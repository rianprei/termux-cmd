# termux-cmd

> **Native Windows CMD (Server 2003) ported to Termux** — Zero dependencies, zero emulation, pure ELF ARM64.

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/yourusername/termux-cmd/actions)
[![Platform](https://img.shields.io/badge/platform-Termux%20(ARM64)-blue)](https://termux.dev)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![Version](https://img.shields.io/badge/version-1.0.0-orange)](https://github.com/yourusername/termux-cmd/releases)

---

## 🎯 Overview

`termux-cmd` is a **native port of Microsoft's Windows Server 2003 `cmd.exe`** to Termux (Android/Linux ARM64). No chroot, no proot, no Wine, no Box64/QEMU — just a clean ELF binary built with Termux's clang toolchain against bionic libc.

### Why this exists

| Approach | Status |
|----------|--------|
| `proot-distro` + Windows | ❌ Slow, heavy |
| `wine` / `box86` / `box64` | ❌ x86 emulation overhead |
| `qemu-user` | ❌ Syscall translation latency |
| **This project** | ✅ **Native ARM64, direct syscalls** |

---

## ✨ Features

| Category | Commands |
|----------|----------|
| **Navigation** | `cd`, `chdir`, `pwd` |
| **Filesystem** | `dir`, `type`, `copy`, `del`, `ren`, `move`, `md`, `rd` |
| **Attributes** | `attrib` |
| **Environment** | `set`, `path`, `ver`, `vol` |
| **Batch/Control** | `if`, `for`, `goto`, `call`, `shift`, `pause`, `rem` |
| **Console** | `cls`, `echo`, `title`, `prompt`, `date`, `time` |
| **Redirection** | `>`, `>>`, `<`, `|` (pipes) |
| **Wildcards** | `*`, `?` with recursive `/s` support |

### Compatibility

- ✅ **Batch scripts** (`.bat`, `.cmd`) — full parser
- ✅ **Interactive mode** — prompt, history, tab-completion
- ✅ **Pipe/Redirect** — stdin/stdout/stderr
- ✅ **Unicode/ANSI** — CP437/CP850/UTF-8 via iconv shim
- ⚠️ **External executables** — limited (no PE loader, uses `CreateProcess` shim → `execve`)

---

## 📦 Installation

### Prerequisites

- Termux (F-Droid or GitHub release)
- `clang`, `make`, `git` (for building)

```bash
pkg install clang make git
```

### Quick Install (Prebuilt)

```bash
# Download latest release
curl -L -o cmd https://github.com/yourusername/termux-cmd/releases/latest/download/cmd-arm64
chmod +x cmd
mv cmd $PREFIX/bin/cmd
```

### Build from Source

```bash
git clone https://github.com/yourusername/termux-cmd.git
cd termux-cmd
make clean && make
cp cmd.exe $PREFIX/bin/cmd
```

### Verify

```bash
cmd /c "ver && echo OK"
# Microsoft Windows [Version 4.0.0000]
# OK
```

---

## 🚀 Usage

### Interactive Shell

```bash
$ cmd
Microsoft Windows [Version 4.0.0000]
(C) Copyright 1985-2003 Microsoft Corp.

C:\data\data\com.termux\files\home>dir
 Volume in drive C is ROOT
 Volume Serial Number is 1234-5678

 Directory of C:\data\data\com.termux\files\home

08/11/2026  14:30    <DIR>          .
08/11/2026  14:30    <DIR>          ..
08/11/2026  14:25               123 test.txt
               1 File(s)            123 bytes
               2 Dir(s)             0 bytes free

C:\data\data\com.termux\files\home>
```

### Batch Execution

```bash
# Single command
cmd /c "dir /b"

# Batch file
cmd /c script.bat

# Interactive with init script
cmd /k init.bat
```

### Path Translation

| Windows | Termux |
|---------|--------|
| `C:\` | `/` |
| `C:\Users\` | `/data/data/com.termux/files/home/` |
| `C:\Windows\System32` | `/system/bin/` |
| `D:\` | `/sdcard/` (if mounted) |

---

## 🏗 Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    termux-cmd (ELF ARM64)                   │
├─────────────────────────────────────────────────────────────┤
│  cmd.c / cmdexec.c  │  Core interpreter, dispatcher         │
│  clex.c / cparse.c  │  Lexer, parser, tokenizer             │
│  ctools*.c          │  Path, file, string utilities         │
│  cpwork.c / cfile.c │  Copy/move/rename/attrib implementations│
│  dir.c / display.c  │  Directory listing, formatting        │
│  cenv.c / cpath.c   │  Environment, PATH handling           │
├─────────────────────────────────────────────────────────────┤
│  portable/ (POSIX Shim Layer)                               │
│  ├── _file.c      │  CreateFile, ReadFile, GetFullPathName  │
│  ├── _find.c      │  FindFirstFile, FindNextFile (glob)     │
│  ├── _msg.c       │  FormatMessage, message tables          │
│  ├── _locale.c    │  GetLocaleInfo, GetTime/DateFormat      │
│  ├── _path.c      │  _splitpath, DOS↔UNIX path conversion   │
│  ├── _time.c      │  Time/date helpers                      │
│  ├── _error.c     │  GetLastError/SetLastError              │
│  └── compat.h     │  Win32 type definitions, inline shims   │
└─────────────────────────────────────────────────────────────┘
```

### Key Design Decisions

| Challenge | Solution |
|-----------|----------|
| Win32 `HANDLE` → POSIX `fd` | Dual handle table (low=fd, high=FILE*) |
| `C:\path` → `/path` | `DOSPath2UNIXPath` / `UNIXPath2DOSPath` |
| `FindFirstFile` | `glob()` with `GLOB_PERIOD` |
| `FormatMessage` | Custom message table + `snprintf` |
| `GetLocaleInfo` | Hardcoded PT-BR locale data |
| `GetTimeFormat` | `strftime` with Windows→POSIX format conversion |

---

## 📚 Documentation

| Document | Description |
|----------|-------------|
| [Installation Guide](docs/install.md) | Detailed build/install steps |
| [Command Reference](docs/commands.md) | All supported commands with syntax |
| [Batch Scripting](docs/batch.md) | Writing `.bat`/`.cmd` scripts |
| [Architecture](docs/architecture.md) | Deep dive into internals |
| [Porting Guide](docs/porting.md) | Adding new commands/shims |
| [Troubleshooting](docs/troubleshooting.md) | Common issues & fixes |

---

## 🛠 Development

### Build Commands

```bash
# Clean build
make clean && make

# Debug build (with symbols)
CFLAGS="-g -O0 -fno-omit-frame-pointer" make

# Run tests
make test
```

### Project Structure

```
termux-cmd/
├── *.c, *.h              # Core source (from Win2K3 leak)
├── portable/             # POSIX shim layer
│   ├── *.c, *.h
│   └── compat.h          # Win32 typedefs + inline shims
├── Makefile              # Build system
├── cmdmsg.mc             # Message compiler input
├── parsemsg.py           # Message compiler (Python)
├── docs/                 # Documentation
├── tests/                # Test suite
├── scripts/              # Build/release helpers
└── .github/              # CI/CD workflows
```

### Adding a New Builtin

1. Add prototype to `cmdproto.h`
2. Add entry to `aAllCommands[]` in `cmdexec.c`
2. Implement `cmdexec_CmdXxx()` in `cmdexec.c`
3. Add help strings to `cmdmsg.mc`
4. Run `python3 parsemsg.py` to regenerate `cmdmsg.c`
5. Rebuild: `make clean && make`

---

## 🧪 Testing

```bash
# Run full test suite
./run_tests.sh

# Individual test categories
./test_builtins.sh      # Core commands
./test_batch.sh         # Batch scripting
./test_paths.sh         # Path translation
./test_wildcards.sh     # Glob/pattern matching
```

### CI/CD

- GitHub Actions: builds on every push
- Tests run on ARM64 Termux container
- Artifacts uploaded as release candidates

---

## 📋 Roadmap

| Version | Target |
|---------|--------|
| **1.0** | ✅ Core commands, batch, pipes |
| **1.1** | External executable support (PE loader stub) |
| **1.2** | Tab completion, command history |
| **1.3** | Unicode/UTF-8 full support |
| **2.0** | Plugin system for custom commands |

---

## 🤝 Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### Quick Checklist

- [ ] Code follows existing style (K&R, tabs=4)
- [ ] New shims go in `portable/`
- [ ] Message strings in `cmdmsg.mc`
- [ ] Tests added for new functionality
- [ ] Documentation updated

---

## ⚖️ License

**MIT License** — see [LICENSE](LICENSE) for details.

This project is based on **Microsoft Windows Server 2003 `cmd.exe` source code** (leaked 2004, publicly archived). Original copyright Microsoft Corporation. This port contains significant modifications for POSIX/Termux compatibility.

---

## 🙏 Acknowledgments

- **Microsoft** — Original `cmd.exe` source (Windows Server 2003)
- **Termux Team** — Excellent ARM64 Linux environment
- **Community** — Testing, bug reports, patches

---

## 📞 Support

- **Issues**: [GitHub Issues](https://github.com/yourusername/termux-cmd/issues)
- **Discussions**: [GitHub Discussions](https://github.com/yourusername/termux-cmd/discussions)
- **Security**: Email security@yourusername.com

---

<p align="center">
  <strong>Made with ❤️ for the Termux community</strong><br>
  <em>Native Windows CMD on Android — no emulation required</em>
</p>