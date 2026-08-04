#!/usr/bin/env python3
"""Keep the CAN Triple programming configuration identical across every project.

Every CAN Triple is programmed with an STLINK-V3MINI, but the OpenOCD version that
PlatformIO installs differs from machine to machine:

  * old OpenOCD (<= 0.11)  -> interface/stlink.cfg selects the deprecated "hla"
                              driver, whose only SWD transport is "hla_swd"
  * new OpenOCD (0.12+dev) -> interface/stlink.cfg selects the "st-link" DAP
                              driver, whose SWD transport is "swd"
                              ("dapdirect_swd" still works but is deprecated)

PlatformIO's ststm32 platform hardcodes "transport select hla_swd", so on an
up-to-date machine every upload/debug dies with:

    Error: Debug adapter doesn't support 'hla_swd' transport

The fix lives in the board definition (boards/CAN_Triple.json) so that BOTH
`pio run -t upload` and `pio debug` use the same OpenOCD invocation, which picks
the transport at runtime instead of assuming one.

This script copies the canonical files kept next to it - boards/CAN_Triple.json
and scripts/build_flags.py - into every project, and verifies that each
platformio.ini still uses the shared setup instead of a local workaround.

Usage:
    python "Programming Tools/sync_programming_config.py"            # apply
    python "Programming Tools/sync_programming_config.py" --check    # verify only (CI/pre-commit)
    python "Programming Tools/sync_programming_config.py" --doctor   # report this machine's OpenOCD
"""

import argparse
import configparser
import json
import os
import subprocess
import sys
from pathlib import Path

TOOLS_DIR = Path(__file__).resolve().parent
REPO_ROOT = TOOLS_DIR.parent
CANONICAL_BOARD = TOOLS_DIR / "CAN_Triple.json"

BOARD_RELATIVE = Path("boards") / "CAN_Triple.json"

# (canonical file in this folder, where it belongs inside every project)
SHARED_FILES = (
    (CANONICAL_BOARD, BOARD_RELATIVE),
    (TOOLS_DIR / "build_flags.py", Path("scripts") / "build_flags.py"),
)

# platformio.ini options that must be the same in every project for programming
# to behave identically. Anything else in the file is project specific.
REQUIRED_OPTIONS = {
    "board": "CAN_Triple",
    "upload_protocol": "stlink",
    "debug_tool": "stlink",
}

# Options that used to carry per-machine OpenOCD workarounds. They override the
# shared board definition, so they must not come back.
FORBIDDEN_OPTIONS = ("debug_server", "upload_command", "debug_port")


def find_projects(root):
    """Every directory under `root` that contains a platformio.ini."""
    skip = (".pio", ".git", "node_modules")
    return sorted(
        p.parent
        for p in root.rglob("platformio.ini")
        if not any(part in skip for part in p.parts)
    )


def read_json(path):
    with open(path, "r", encoding="utf-8") as handle:
        return json.load(handle)


def without_debug_tools(board):
    """A copy of a board manifest with the debug tool definitions removed."""
    clone = json.loads(json.dumps(board))
    clone.get("debug", {}).pop("tools", None)
    return clone


def sync_board(target, canonical_text, check_only):
    """Install the shared ST-Link definition without losing local board tweaks.

    Some projects legitimately customise their board file (the GUI firmware caps
    `maximum_size` at 64 KB for the dual-bank linker script). Those keep their
    settings and only receive the debug/upload tool block.
    """
    label = BOARD_RELATIVE.as_posix()
    canonical = json.loads(canonical_text)
    shared_tool = canonical["debug"]["tools"]["stlink"]

    if not target.is_file():
        if check_only:
            return "stale", "%s MISSING" % label
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(canonical_text, encoding="utf-8")
        return "updated", "%s MISSING -> created" % label

    current_text = target.read_text(encoding="utf-8")
    if current_text == canonical_text:
        return "ok", None

    try:
        current = read_json(target)
    except ValueError as exc:
        return "stale", "%s is not valid JSON (%s)" % (label, exc)

    customised = without_debug_tools(current) != without_debug_tools(canonical)
    if customised and current.get("debug", {}).get("tools", {}).get("stlink") == shared_tool:
        return "ok", None

    if check_only:
        return "stale", "%s OUT OF DATE" % label

    if customised:
        current.setdefault("debug", {}).setdefault("tools", {})["stlink"] = shared_tool
        target.write_text(json.dumps(current, indent=2) + "\n", encoding="utf-8")
        return "updated", "%s patched (local board settings kept)" % label

    target.write_text(canonical_text, encoding="utf-8")
    return "updated", "%s OUT OF DATE -> rewritten" % label


def sync_shared_files(project, check_only):
    """Copy the canonical files into a project. Returns (status, details)."""
    status = "ok"
    details = []
    for canonical, relative in SHARED_FILES:
        target = project / relative
        canonical_text = canonical.read_text(encoding="utf-8")

        if relative == BOARD_RELATIVE:
            file_status, detail = sync_board(target, canonical_text, check_only)
            if detail:
                details.append(detail)
            if file_status != "ok":
                status = file_status
            continue

        if target.is_file():
            if target.read_text(encoding="utf-8") == canonical_text:
                continue
            detail = "%s OUT OF DATE" % relative.as_posix()
        else:
            # Only projects that actually run the pre-build script get a copy.
            if not references_script(project, relative.name):
                continue
            detail = "%s MISSING" % relative.as_posix()

        if check_only:
            status = "stale"
            details.append(detail)
            continue

        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(canonical_text, encoding="utf-8")
        status = "updated"
        details.append(detail + " -> rewritten")
    return status, details


def references_script(project, script_name):
    """True if platformio.ini runs the given extra script."""
    try:
        return script_name in (project / "platformio.ini").read_text(
            encoding="utf-8", errors="replace"
        )
    except OSError:
        return False


def check_ini(project):
    """Return a list of problems found in the project's platformio.ini."""
    ini_path = project / "platformio.ini"
    parser = configparser.ConfigParser(
        interpolation=None, strict=False, inline_comment_prefixes=(";",)
    )
    try:
        parser.read(ini_path, encoding="utf-8")
    except configparser.Error as exc:
        return ["platformio.ini could not be parsed: %s" % exc]

    envs = [s for s in parser.sections() if s.startswith("env:")]
    if not envs:
        return ["platformio.ini has no [env:...] section"]

    problems = []
    for section in envs:
        for option, expected in REQUIRED_OPTIONS.items():
            actual = (parser.get(section, option, fallback="") or "").strip()
            if actual != expected:
                problems.append(
                    "[%s] %s = %s (expected %s)"
                    % (section, option, actual or "<missing>", expected)
                )
        for option in FORBIDDEN_OPTIONS:
            if parser.has_option(section, option):
                problems.append(
                    "[%s] %s overrides the shared board definition - remove it"
                    % (section, option)
                )
        for script in (parser.get(section, "extra_scripts", fallback="") or "").split():
            if "openocd" in script.lower():
                problems.append(
                    "[%s] extra_scripts runs %s - a local OpenOCD workaround, "
                    "superseded by the shared board definition" % (section, script)
                )
    return problems


def openocd_report():
    """Describe the OpenOCD this machine will actually use."""
    core_dir = Path(
        os.environ.get("PLATFORMIO_CORE_DIR", Path.home() / ".platformio")
    )
    packages = sorted((core_dir / "packages").glob("tool-openocd*"))
    if not packages:
        print("No tool-openocd package found under %s" % (core_dir / "packages"))
        print("PlatformIO installs it on the first upload for this board.")
        return 1

    for package in packages:
        print("-" * 72)
        print("package : %s" % package)
        manifest = package / "package.json"
        if manifest.is_file():
            try:
                print("version : %s" % read_json(manifest).get("version", "?"))
            except ValueError:
                pass

        stlink_cfg = package / "openocd" / "scripts" / "interface" / "stlink.cfg"
        if stlink_cfg.is_file():
            body = stlink_cfg.read_text(encoding="utf-8", errors="replace")
            if "adapter driver hla" in body:
                flavour = "HLA driver  -> this machine needs 'hla_swd'"
            elif "adapter driver st-link" in body:
                flavour = "ST-Link DAP -> this machine needs 'swd'"
            else:
                flavour = "unrecognised"
            print("stlink.cfg: %s" % flavour)
        else:
            print("stlink.cfg: MISSING (%s)" % stlink_cfg)

        binary = package / "bin" / ("openocd.exe" if os.name == "nt" else "openocd")
        if not binary.is_file():
            binary = package / "bin" / "openocd"
        if not binary.is_file():
            print("binary    : MISSING")
            continue

        board = read_json(CANONICAL_BOARD)
        args = [
            arg.replace("$PACKAGE_DIR", str(package))
            for arg in board["debug"]["tools"]["stlink"]["server"]["arguments"]
        ]
        # Parse the shared configuration without touching the hardware.
        cmd = (
            [str(binary)]
            + args
            + ["-c", "echo [transport select]", "-c", "exit"]
        )
        print("probing   : %s" % binary)
        try:
            proc = subprocess.run(
                cmd, capture_output=True, text=True, timeout=30, check=False
            )
        except OSError as exc:
            print("transport : could not run OpenOCD (%s)" % exc)
            continue
        output = (proc.stdout or "") + (proc.stderr or "")
        transport = next(
            (
                line.strip()
                for line in output.splitlines()
                if line.strip().startswith(("swd", "hla_swd", "dapdirect_swd"))
            ),
            None,
        )
        if transport:
            print("transport : %s (selected by the shared board config)" % transport)
        else:
            print("transport : could not be determined, raw output follows")
            print(output.strip())
    print("-" * 72)
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument(
        "--check",
        action="store_true",
        help="report differences without writing anything (exit 1 if out of sync)",
    )
    parser.add_argument(
        "--doctor",
        action="store_true",
        help="show which OpenOCD/transport this machine will use, then exit",
    )
    parser.add_argument(
        "--root",
        action="append",
        metavar="PATH",
        help="extra folder to scan for PlatformIO projects (repeatable). "
        "Defaults to the CAN_Triple repository this script lives in.",
    )
    options = parser.parse_args()

    if not CANONICAL_BOARD.is_file():
        print("Canonical board file missing: %s" % CANONICAL_BOARD)
        return 2

    if options.doctor:
        return openocd_report()

    for canonical, _ in SHARED_FILES:
        if not canonical.is_file():
            print("Canonical file missing: %s" % canonical)
            return 2

    roots = [Path(r).resolve() for r in options.root] if options.root else [REPO_ROOT]
    for root in roots:
        if not root.is_dir():
            print("Not a folder: %s" % root)
            return 2

    projects = []
    seen = set()
    for root in roots:
        for project in find_projects(root):
            if project in seen:
                continue
            seen.add(project)
            projects.append((project, root))
    if not projects:
        print("No PlatformIO projects found under %s" % ", ".join(str(r) for r in roots))
        return 2

    issues = 0
    rewritten = 0
    for project, root in projects:
        name = root.name if project == root else project.relative_to(root).as_posix()
        status, details = sync_shared_files(project, options.check)
        problems = check_ini(project)

        if status == "stale":
            issues += len(details)
        elif status == "updated":
            rewritten += len(details)
        issues += len(problems) if options.check else 0

        if status == "ok" and not problems:
            print("  ok      %s" % name)
            continue

        marker = {"ok": "  ok    ", "updated": "  fixed ", "stale": "  STALE "}[status]
        print("%s  %s" % (marker, name))
        for line in details + problems:
            print("            %s" % line)

    print()
    print("%d project(s) scanned" % len(projects))
    if options.check:
        if issues:
            print("%d issue(s) found - run without --check to fix the shared files" % issues)
            return 1
        print("all projects share the same programming configuration")
        return 0

    print("%d file(s) rewritten" % rewritten)
    return 0


if __name__ == "__main__":
    sys.exit(main())
