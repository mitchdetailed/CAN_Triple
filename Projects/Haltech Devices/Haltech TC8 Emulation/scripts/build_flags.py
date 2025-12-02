import subprocess
import sys

def install_module(module_name):
    subprocess.check_call([sys.executable, '-m', 'pip', 'install', module_name])

# Example usage
try:
    from SCons.Script import Import
except ImportError:
    print("SCons not found, installing now...")
    install_module('scons')
    from SCons.Script import Import

import os
import re


Import("env")

# Regex patterns for all printf/scanf variations
printf_pattern = r"\b(v?f?|s?)printf\s*\("
scanf_pattern = r"\b(v?f?|s?)scanf\s*\("

# Regex patterns for comments
single_line_comment = re.compile(r"^\s*//")  # Matches lines starting with //
multi_line_comment_start = re.compile(r"/\*")  # Matches /*
multi_line_comment_end = re.compile(r"\*/")  # Matches */

def check_float_usage(src_dir):
    """Scan source files to check if printf or scanf variations are used (ignoring comments).
       Returns: (needs_printf, needs_scanf, occurrences)
    """
    needs_printf = False
    needs_scanf = False
    occurrences = []  # Store (file, line_number, function) for logging
    inside_comment_block = False  # Track multi-line comment blocks

    for root, _, files in os.walk(src_dir):
        for file in files:
            if file.endswith(".c") or file.endswith(".cpp"):
                file_path = os.path.join(root, file)
                with open(file_path, "r", encoding="utf-8") as f:
                    for line_number, line in enumerate(f, start=1):
                        line = line.strip()

                        # Track if we're inside a /* multi-line comment block */
                        if inside_comment_block:
                            if multi_line_comment_end.search(line):
                                inside_comment_block = False
                            continue  # Skip commented-out lines

                        if multi_line_comment_start.search(line):
                            inside_comment_block = True
                            continue  # Skip the start of comment block

                        # Ignore single-line comments
                        if single_line_comment.match(line):
                            continue

                        # Check for printf and scanf variants in non-commented lines
                        printf_match = re.search(printf_pattern, line)
                        scanf_match = re.search(scanf_pattern, line)

                        if printf_match:
                            needs_printf = True
                            occurrences.append((file_path, line_number, printf_match.group(0)))

                        if scanf_match:
                            needs_scanf = True
                            occurrences.append((file_path, line_number, scanf_match.group(0)))

    return needs_printf, needs_scanf, occurrences

# Get the source directory (Modify if necessary)
src_dir = os.path.join(env["PROJECT_DIR"], "src")

# Check for float-related functions
needs_printf, needs_scanf, occurrences = check_float_usage(src_dir)

# Add flags dynamically based on which functions are used
if needs_printf:
    env.Append(LINKFLAGS=["-Wl,-u,_printf_float"])
    print("✅ Float support enabled for printf-family functions")

if needs_scanf:
    env.Append(LINKFLAGS=["-Wl,-u,_scanf_float"])
    print("✅ Float support enabled for scanf-family functions")

if not (needs_printf or needs_scanf):
    print("ℹ️ Float support not required")

# Print where printf or scanf was found
if occurrences:
    print("\n🔍 Found printf/scanf in the following locations:")
    for file, line_number, function in occurrences:
        print(f"   - {file} (line {line_number}): {function}")
