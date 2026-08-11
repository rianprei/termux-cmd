# Changelog

All notable changes to this project will be documented in this format.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [1.0.0] - 2026-08-11

### Added

- **Core Interpreter**: Full Windows Server 2003 `cmd.exe` port to Termux ARM64
- **Builtin Commands** (30+):
  - Navigation: `cd`, `chdir`, `pwd`
  - Filesystem: `dir`, `type`, `copy`, `del`, `ren`, `move`, `md`, `rd`
  - Attributes: `attrib`
  - Environment: `set`, `path`, `ver`, `vol`
  - Batch/Control: `if`, `for`, `goto`, `call`, `shift`, `pause`, `rem`
  - Console: `cls`, `echo`, `title`, `prompt`, `date`, `time`
- **POSIX Shim Layer** (`portable/`):
  - `CreateFile`, `ReadFile`, `WriteFile`, `CloseHandle`
  - `GetFullPathName`, `GetFileAttributes`, `SetFileAttributes`
  - `FindFirstFile`, `FindNextFile`, `FindClose` (via `glob()`)
  - `FormatMessage`, `GetLocaleInfo`, `GetTimeFormat`, `GetDateFormat`
  - `_splitpath`, `DOSPath2UNIXPath`, `UNIXPath2DOSPath`
  - `GetLastError`/`SetLastError` mapping to `errno`
- **Batch Scripting**: Full parser with `if`, `for`, `goto`, `call`, `shift`
- **Redirection & Pipes**: `>`, `>>`, `<`, `|` support
- **Wildcards**: `*`, `?` with recursive `/s` support
- **Path Translation**: `C:\` ↔ `/`, drive mapping, UNC stubs
- **Message System**: Windows-compatible message tables (PT-BR locale)

### Fixed

- `GetFullPathName` handling of root paths (`C:\`) and wildcards
- `FormatMessage` `FORMAT_MESSAGE_ALLOCATE_BUFFER` support
- `GetLocaleInfo` returning proper `BOOL` (1/0) not `SUCCESS` (0)
- `GetTimeFormat`/`GetDateFormat` Windows→POSIX format conversion
- `ReadFile` line-buffering for pipe input (multi-command support)
- `MoveFile` / `MoveFileEx` path conversion for `rename(2)`
- `ScanFSpec` accepting both `/` and `\` as path separators

### Changed

- Build system: Single `Makefile` with `clang` + bionic
- Removed all Windows CE dependencies (clean NT-based port)
- Unified error handling via `GetLastError`/`SetLastErrno`
- Modernized `Makefile` with debug/release targets

### Removed

- All CE-specific APIs (`coredll.dll`, `Ce*`, `GetStdioPathW`, etc.)
- `LocalAlloc`/`LocalFree` replaced with `malloc`/`free`
- Thread-based Ctrl-C handler (replaced with POSIX signal + `siglongjmp`)

---

## [0.9.0] - 2026-08-01 (Pre-release)

### Added

- Initial NT-based cmd.exe port to Termux
- Basic `dir`, `cd`, `type`, `copy`, `del` working
- POSIX shim layer skeleton

### Known Issues

- `ren` with forward slashes failed
- Multi-command pipes broken (ReadFile consumed entire buffer)
- `dir /s` recursion not implemented
- Date/time format wrong (US vs PT-BR)

---

## [Unreleased]

### Planned

- Tab completion (`TAB`)
- Command history (`F7`, `Up/Down`)
- External executable support (PE loader stub)
- Full Unicode/UTF-8 support
- Plugin system for custom commands

---

## Versioning

This project follows [SemVer](https://semver.org/). Versions are tagged as `vX.Y.Z`.

- **Major**: Breaking API/ABI changes
- **Minor**: New commands, features, backward-compatible
- **Patch**: Bug fixes, internal improvements

---

## Release Process

1. Update `CHANGELOG.md`
2. Update version in `Makefile`/`cmd.h`
3. Create signed tag: `git tag -s v1.0.0 -m "Release 1.0.0"`
4. Push tag: `git push origin v1.0.0`
5. GitHub Actions builds and creates release
5. Update documentation