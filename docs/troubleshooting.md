# Troubleshooting

## Build Issues

### `clang: command not found`

```bash
pkg install clang make git
```

### `fatal error: windows.h: No such file or directory`

```bash
# Ensure portable/compat.h is included first
#include "portable/compat.h"  // defines Windows types
#include "cmd.h"
```

### `undefined reference to 'GetLastError'`

```bash
# Link the error shim
make clean
make  # ensures portable/_error.o is linked
```

### `multiple definition of 'MoveFile'`

Check `ctools3.c` vs `portable/_file.c` — only one should implement.

```bash
grep -n "MoveFile" *.c portable/*.c
# Remove duplicate from ctools3.c if portable/_file.c has it
```

### `error: 'SUCCESS' undeclared`

```c
#include "cmd.h"  // defines SUCCESS=0, FAILURE=1
```

---

## Runtime Issues

### `cmd: not found`

```bash
# Ensure binary in PATH
cp cmd.exe $PREFIX/bin/cmd
echo $PATH | grep -q "$PREFIX/bin" || export PATH=$PREFIX/bin:$PATH
```

### `Permission denied`

```bash
chmod +x cmd.exe
```

### `Segmentation fault` / `SIGSEGV`

```bash
# Build with debug symbols
make DEBUG=1

# Run under GDB
gdb ./cmd.exe
(gdb) run /c "command"
(gdb) bt
```

Common causes:
- Uninitialized pointer in shim
- Buffer overflow in path handling
- Double-free in `cmdutil_Free`
- `FindFirstFile` returning invalid handle

### `dir` shows no files / wrong directory

```bash
# Check path translation
cmd /c "pwd"
cmd /c "cd .. && pwd"

# Verify DOSPath2UNIXPath
cmd /c "copy file.txt /data/data/com.termux/files/home/test.txt"
```

### `copy` / `ren` / `del` fails with "The system cannot find the file specified"

```bash
# Check path separators
cmd /c "copy file.txt dest.txt"      # relative
cmd /c "copy ./file.txt ./dest.txt"  # explicit
cmd /c "copy C:\file.txt C:\dest.txt"  # DOS paths
```

### `date` / `time` shows wrong format

```bash
# Verify locale shim
cmd /c "date /T"
cmd /c "time /T"

# Check locale environment
locale
```

### External commands not found

```bash
# termux-cmd does not execute external ELF binaries
# Use Termux shell directly for non-builtins:
ls
cp file1 file2
```

---

## Debugging Techniques

### Enable Debug Logs

```bash
make DEBUG=1
./cmd.exe /c "command" 2>&1 | grep DEBUG
```

### Trace Syscalls

```bash
strace -f -e trace=openat,read,write,close,mmap,execve ./cmd.exe /c "command"
```

### Memory Issues

```bash
# Build with AddressSanitizer
make CFLAGS="-fsanitize=address -fno-omit-frame-pointer"
./cmd.exe /c "command"
```

### GDB Breakpoints

```bash
gdb ./cmd.exe
(gdb) break cmdexec_CmdCopy
(gdb) run /c "copy a.txt b.txt"
(gdb) bt
```

---

## Common Error Codes

| Win32 Error | errno | Meaning | Fix |
|-------------|-------|---------|-----|
| `ERROR_FILE_NOT_FOUND` | ENOENT | File missing | Check path translation |
| `ERROR_PATH_NOT_FOUND` | ENOENT | Dir missing | Check parent dirs |
| `ERROR_ACCESS_DENIED` | EACCES | No permission | Check file perms |
| `ERROR_INVALID_HANDLE` | EBADF | Bad fd | Check `CreateFile` return |
| `ERROR_NOT_ENOUGH_MEMORY` | ENOMEM | OOM | Reduce buffer sizes |
| `ERROR_INVALID_PARAMETER` | EINVAL | Bad arg | Validate inputs |
| `ERROR_ALREADY_EXISTS` | EEXIST | File exists | Use `/Y` or delete first |
| `ERROR_DISK_FULL` | ENOSPC | No space | Free storage |

---

## Getting Help

1. **Search existing issues** — [GitHub Issues](https://github.com/rianprei/termux-cmd/issues)
2. **Run with debug** — `make DEBUG=1 && ./cmd.exe /c "cmd" 2>&1`
3. **Include in report**:
   - `uname -a`
   - `pkg list-installed | grep -E "clang|make|termux"`
   - Full command that fails
   - Expected vs actual output
   - `strace` output if segfault