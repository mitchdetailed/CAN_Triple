# DBC → C Code Generator (Qt GUI)

Desktop tool that replaces the old `DBC to C Code Unified Tool.py`. Load a `.dbc`,
pick which messages/signals you want and whether each is **Rx** or **Tx**, then
export a ready-to-compile `.c` / `.h` pair plus a customer integration `.txt`.

It is **self-contained**: a small built-in DBC parser (no `cantools`/Python) so
customers can build and run it with only Qt.

## What it does

- **Load DBC** → messages shown in a tree, signals nested underneath, with
  checkboxes. Unchecking a message unchecks all of its signals.
- Per message you set:
  - **Type**: Blank / Rx / Tx
  - **Bus**: CAN 1 / CAN 2 / CAN 3
  - If **Rx**: a **Forward** checkbox and a **Fwd Bus** (the receive bus is
    excluded so a frame is never forwarded back onto the bus it arrived on).
  - If **Tx**: a **Tx Freq** from the rates the firmware scheduler supports
    (1, 2, 5, 10, 20, 50, 100, 200 Hz). `GenMsgCycleTime` in the DBC pre-fills it.
  - If **Tx** and multiplexed: **Mux Mode** = Batch (all groups each tick) or
    Sequential (one group per tick, cycling).
- Per signal (bottom table) you set: **On**, **DPS** (decimal places) and the
  **Returned Data Type** (auto-inferred default from range/scale/offset; editable
  dropdown). Signals with a value table become a C `enum` automatically.
- **Export** writes `<name>.c`, `<name>.h`, `<name>_instructions.txt` (named off
  the DBC by default). Value-table enumerators are emitted as
  `SIGNALNAME_ENUMERATOR` (all caps).

The generated code plugs into the firmware's model: a `<name>_CAN_Receive()` you
call from `onReceive()`, and `<name>_Events_<N>Hz()` functions you call from the
matching `events_<N>Hz()` handlers. Full wiring notes are in the exported `.txt`.

## Build

Prerequisites: **Qt 6** (Widgets) + **CMake ≥ 3.16** + a C++17 compiler.
This machine already has Qt 6.7.2 (mingw_64) and its MinGW toolchain.

### Command line (MinGW)

```sh
cd tools/DbcCodegenGui
# put Qt's mingw + Qt bin on PATH
export PATH="/c/Qt/Tools/mingw1120_64/bin:/c/Qt/6.7.2/mingw_64/bin:$PATH"
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.7.2/mingw_64"
cmake --build build -j
# run:
./build/DbcCodegenGui.exe
```

### Qt Creator

Open `CMakeLists.txt` as a project, select the Qt 6.7.2 MinGW kit, Build & Run.

### Deploying to another PC

The exe needs the Qt runtime DLLs **and** the MinGW runtime DLLs. From a Qt
command prompt:

```sh
windeployqt --release --compiler-runtime build/DbcCodegenGui.exe
```

`--compiler-runtime` also copies `libgcc_s_seh-1.dll`, `libstdc++-6.dll` and
`libwinpthread-1.dll`. If your windeployqt build doesn't pull them in, copy them
manually from `C:/Qt/Tools/mingw1120_64/bin` next to the exe. After this the exe
runs on machines without Qt installed (verified here with a clean PATH).

## Source layout

| File | Purpose |
|------|---------|
| `dbc.h` | Data model + pure helpers (start-bit conversion, type inference, sanitizing). No Qt. |
| `dbcparser.{h,cpp}` | Minimal DBC parser: `BO_`, `SG_` (incl. mux), `BU_`, `VAL_`, `SIG_VALTYPE_`, `BA_ GenMsgCycleTime`. No Qt. |
| `codegen.{h,cpp}` | Emits the `.c` / `.h` / `.txt` strings. No Qt. |
| `mainwindow.{h,cpp}` | The Qt UI (tree, per-message controls, signal table, export). |
| `main.cpp` | Entry point. |

Because the parser/generator are Qt-free, they can be unit-tested with a plain
`g++` driver (see the project history) or reused in a CLI build later.

## Notes / limitations

- Big-endian (Motorola) start bits are converted to the LSB numbering the
  firmware's `dbc_decode`/`dbc_encode` expect — identical to the original Python
  tool, so generated bit positions match byte-for-byte.
- Extended (29-bit) IDs are detected from the DBC id's high bit.
- Extended/complex multiplexing (multiple mux selectors) is not handled; simple
  `M` + `m<n>` multiplexing is.
