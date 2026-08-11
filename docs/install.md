# Installation Guide

## Prerequisites

- **Termux** (F-Droid build recommended, or GitHub release ≥ 0.118)
- **Architecture**: ARM64 (aarch64) — x86_64 not tested
- **Android**: 7.0+ (API 24+)
- **Storage**: ~10 MB for binary + deps

## Quick Install (Recommended)

```bash
# Install Termux from F-Droid
# Open Termux and run:
pkg update && pkg upgrade -y
pkg install clang make git

# Clone and build
git clone https://github.com/yourusername/termux-cmd.git
cd termux-cmd
make clean && make

# Install to PATH
cp cmd.exe $PREFIX/bin/cmd
```

## Verify Installation

```bash
cmd /c "ver && echo Installation successful"
# Microsoft Windows [Version 4.0.0000]
# Installation successful
```

## Build Options

| Target | Command | Description |
|--------|---------|-------------|
| Release | `make` | Optimized (`-O2`) |
| Debug | `make DEBUG=1` | Symbols, no optimization |
| Clean | `make clean` | Remove all objects |
| Test | `make test` | Run test suite |

### Environment Variables

```bash
# Custom install prefix
make PREFIX=/data/data/com.termux/files/usr

# Cross-compile (if needed)
make CC=aarch64-linux-android-clang
```

---

## Troubleshooting

### Build Failures

| Error | Solution |
|-------|----------|
| `clang: command not found` | `pkg install clang` |
| `fatal error: windows.h: No such file` | Use `portable/compat.h` includes |
| `undefined reference to 'GetLastError'` | Link `portable/_error.o` |
| `Multiple definition of 'MoveFile'` | Check `portable/_file.c` vs `ctools3.c` |

### Runtime Issues

| Symptom | Fix |
|---------|-----|
| `cmd: not found` | Ensure `$PREFIX/bin` in `$PATH` |
| `Permission denied` | `chmod +x cmd.exe` |
| `Segmentation fault` | Run with `DEBUG=1 make` + `gdb ./cmd.exe` |
| `dir` shows no files | Check path translation (`C:\` → `/`) |

### Common Commands to Test

```bash
cmd /c "ver"
cmd /c "dir"
cmd /c "cd .. && pwd"
cmd /c "copy file1.txt file2.txt"
cmd /c "md testdir && rd testdir"
```

---

## Uninstall

```bash
rm $PREFIX/bin/cmd
```

---

## Advanced: Cross-Compilation

```bash
# On x86_64 Linux with Android NDK
export NDK=/path/to/android-ndk
export CC=$NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android24-clang
make clean && make CC=$CC
```

---

## Support

- **Issues**: [GitHub Issues](https://github.com/yourusername/termux-cmd/issues)
- **Build Logs**: Include full `make` output
- **Environment**: `uname -a`, `pkg list-installed`, `clang --version`