# Architecture

## Overview

```
┌─────────────────────────────────────────────────────────────────┐
│                        termux-cmd                                │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │  Core Interpreter (cmd.c, cmdexec.c, clex.c, cparse.c) │   │
│  │  - Command parsing, dispatching, execution             │   │
│  │  - Batch file processing, control flow                 │   │
│  │  - Redirection, pipes, environment                     │   │
│  └─────────────────────────────────────────────────────────┘   │
│                              │                                  │
│                              ▼                                  │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │  POSIX Shim Layer (portable/)                           │   │
│  │  - Win32 API → POSIX/bionic translation                │   │
│  │  - Handle management (dual fd/FILE* table)             │   │
│  │  - Path conversion (DOS ↔ UNIX)                        │   │
│  │  - Error mapping (Win32 ↔ errno)                       │   │
│  └─────────────────────────────────────────────────────────┘   │
│                              │                                  │
│                              ▼                                  │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │  Bionic libc / Linux Kernel                             │   │
│  │  - syscalls: openat, read, write, mmap, execve...      │   │
│  │  - bionic libc: malloc, stdio, pthreads, signals       │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
```

## Core Components

### Interpreter (`cmd.c`, `cmdexec.c`, `clex.c`, `cparse.c`)

| File | Responsibility |
|------|----------------|
| `cmd.c` | Main entry, initialization, input loop, prompt |
| `cmdexec.c` | Command dispatch, all builtin implementations |
| `clex.c` | Lexical analysis, tokenization |
| `cparse.c` | Parsing, AST construction |
| `cinfo.c` | Command info table, help system |

### POSIX Shim (`portable/`)

| File | Win32 APIs Implemented |
|------|------------------------|
| `_file.c` | `CreateFile`, `ReadFile`, `WriteFile`, `CloseHandle`, `GetFullPathName`, `GetFileAttributes`, `SetFileAttributes`, `MoveFile`, `DeleteFile` |
| `_find.c` | `FindFirstFile`, `FindNextFile`, `FindClose` (via `glob()`) |
| `_msg.c` | `FormatMessage`, message table lookup |
| `_locale.c` | `GetLocaleInfo`, `GetTimeFormat`, `GetDateFormat` |
| `_path.c` | `_splitpath`, `DOSPath2UNIXPath`, `UNIXPath2DOSPath` |
| `_error.c` | `GetLastError`, `SetLastError`, `SetLastErrno` |
| `_time.c` | Time/date helpers |
| `_memory.c` | `LocalAlloc`, `LocalFree`, `LocalReAlloc` |
| `_ltoa.c` | `_ltoa`, `_ultoa`, `_i64toa` |
| `compat.h` | Win32 type defs, inline shims (`GetFileType`, `WinFmtToStrftime`, etc.) |

### Handle Model

```
Win32 HANDLE (opaque)          POSIX Reality
─────────────────────────────────────────────────
0x00000000 - 0x0000FFFF        stdin/stdout/stderr (0,1,2)
0x00010000 - 0x7FFFFFFF        FILE* (stdio) → fileno()
0x80000000 - 0xFFFFFFFF        Raw fd (openat) + 0x80000000
```

Mapping functions in `portable/compat.h`:
- `CRTTONT(fd)` → Win32 HANDLE
- `NTTORC(handle)` → fd / FILE*

### Path Translation

```
DOS Path                    → UNIX Path
─────────────────────────────────────────────
C:\                         → /
C:\Windows                  → /system/bin
C:\Users\name               → /data/data/com.termux/files/home
D:\                         → /sdcard (if mounted)
\\server\share              → /mnt/server/share (stub)
```

Implementation: `DOSPath2UNIXPath()` / `UNIXPath2DOSPath()` in `_path.c`

### Error Mapping

```
Win32 Error              → errno
────────────────────────────────────────
ERROR_SUCCESS            → 0
ERROR_FILE_NOT_FOUND     → ENOENT
ERROR_PATH_NOT_FOUND     → ENOENT
ERROR_ACCESS_DENIED      → EACCES
ERROR_INVALID_HANDLE     → EBADF
ERROR_NOT_ENOUGH_MEMORY  → ENOMEM
ERROR_INVALID_PARAMETER  → EINVAL
ERROR_ALREADY_EXISTS     → EEXIST
ERROR_DISK_FULL          → ENOSPC
...                      → (see _error.c)
```

---

## Data Flow Example: `copy file1.txt file2.txt`

```
1. Parser (cparse.c)
   └── Tokens: "copy", "file1.txt", "file2.txt"

2. Dispatcher (cmdexec.c)
   └── cmdexec_CmdCopy("copy", "file1.txt file2.txt")

3. Path Resolution (cmdutil.c → _path.c)
   └── DOSPath2UNIXPath("file1.txt") → "./file1.txt"
   └── DOSPath2UNIXPath("file2.txt") → "./file2.txt"

4. Shim Layer (_file.c)
   ├── CreateFile("./file1.txt", GENERIC_READ) 
   │   └── openat(AT_FDCWD, "file1.txt", O_RDONLY) → fd
   │   └── fdopen(fd, "rb") → FILE*
   │
   ├── CreateFile("./file2.txt", GENERIC_WRITE)
   │   └── openat(AT_FDCWD, "file2.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) → fd
   │   └── fdopen(fd, "wb") → FILE*
   │
   ├── ReadFile(src, buf, size) → fread()
   └── WriteFile(dst, buf, size) → fwrite()

5. Cleanup
   └── CloseHandle → fclose() → close(fd)

6. Error Handling
   └── GetLastError() → errno mapping
```

---

## Build System

### Makefile Targets

```makefile
# Core objects
OBJS = cmd.o cmdexec.o clex.o cparse.o cinfo.o ...
# Shim objects
SHIM_OBJS = portable/_file.o portable/_find.o portable/_msg.o ...
# All
ALL_OBJS = $(OBJS) $(SHIM_OBJS)

# Default
cmd.exe: $(ALL_OBJS)
    $(CC) -o $@ $(ALL_OBJS) $(LDFLAGS)

# Debug
DEBUG=1 make  # -g -O0 -DDEBUG
```

### Dependencies

- **Only**: `clang` (Termux), `make`, `python3` (for `parsemsg.py`)
- **No**: `pkg-config`, `cmake`, `autotools`, external libs

---

## Threading & Signals

| Component | Mechanism |
|-----------|-----------|
| Ctrl-C | `SIGINT` handler → `siglongjmp` to input loop |
| Batch abort | `setjmp`/`longjmp` via `CmdJBuf` |
| No threads | Single-threaded event loop |

---

## Memory Management

| Layer | Allocator |
|-------|-----------|
| Core | `malloc`/`free` (via `cmdutil_Alloc`/`cmdutil_Free`) |
| Fixed-size blocks | `LocalAlloc`/`LocalFree` shim (pool allocator) |
| Pointer lists | Fixed-mem pool (`cmdutil_GetFMem`) |

---

## Testing Architecture

```
tests/
├── test_builtins.sh      # All builtins
├── test_batch.sh         # .bat/.cmd execution
├── test_paths.sh         # DOS↔UNIX translation
├── test_wildcards.sh     # Glob patterns, /s recursion
├── test_shims.sh         # Shim correctness
└── test_integration.sh   # End-to-end scenarios
```

Run: `./scripts/run_tests.sh`