# Porting Guide

Guide for adding new commands, shims, or extending the POSIX layer.

---

## Adding a New Builtin Command

### 1. Prototype in `cmdproto.h`

```c
int cmdexec_CmdYourcmd(TCHAR *lpName, TCHAR *lpArgs);
```

### 2. Register in `cmdexec.c`

```c
Command aAllCommands[] = {
    // ... existing ...
    { TEXT("YOURCMD"), IDS_HELP_CMD_YOURCMD, IDS_HELP_EXT_YOURCMD, cmdexec_CmdYourcmd },
};
```

### 3. Implement in `cmdexec.c`

```c
int cmdexec_CmdYourcmd(TCHAR *lpName, TCHAR *lpArgs)
{
    // 1. Parse arguments
    PointerList *pplFiles, *pplOptions;
    int iNum = cmdutil_ParseCommandParameters(pplFiles, pplOptions, lpArgs);
    
    if (pplOptions) {
        // Handle switches
        cmdutil_FixedFreePointerList(pplOptions);
    }
    
    // 2. Process files
    if (pplFiles) {
        PointerList *pplRun = pplFiles;
        while (pplRun) {
            TCHAR *file = (TCHAR *)pplRun->pData;
            // Process each file
            pplRun = pplRun->pNext;
        }
        cmdutil_FixedFreePointerList(pplFiles);
    }
    
    return CMD_SUCCESS;
}
```

### 4. Add Help Strings (`cmdmsg.mc`)

```
MessageId=3050
SymbolicName=IDS_HELP_CMD_YOURCMD
Language=Portuguese
YOURCMD - Brief description.
.

MessageId=3051
SymbolicName=IDS_HELP_EXT_YOURCMD
Language=Portuguese
YOURCMD [/switches] [files]
  /S   Recursive
  /Q   Quiet
Description...
.
```

### 5. Regenerate Messages

```bash
python3 parsemsg.py
make clean && make
```

---

## Adding a New POSIX Shim

### 1. Define Win32 API in `portable/compat.h`

```c
// Type definitions
typedef struct _WIN32_FIND_DATA { ... } WIN32_FIND_DATA, *LPWIN32_FIND_DATA;

// Function prototype
BOOL WINAPI YourWin32API(
    _In_  DWORD  dwParam1,
    _Out_ LPTSTR lpBuffer,
    _In_  DWORD  nSize
);
```

### 2. Implement in `portable/_yourshim.c`

```c
#include "cmd.h"
#include <unistd.h>
#include <errno.h>

BOOL WINAPI YourWin32API(DWORD dwParam1, LPTSTR lpBuffer, DWORD nSize)
{
    // 1. Convert DOS paths if needed
    char *unix_path = DOSPath2UNIXPath(lpParam);
    
    // 2. Call POSIX syscall
    int ret = posix_syscall(unix_path, ...);
    
    // 3. Map errors
    if (ret < 0) {
        SetLastErrno();  // maps errno → Win32 error
        free(unix_path);
        return FALSE;
    }
    
    // 4. Convert result back if needed
    // ...
    
    free(unix_path);
    return TRUE;
}
```

### 3. Add to Build

Edit `Makefile`:
```makefile
SHIM_OBJS = portable/_file.o portable/_find.o portable/_msg.o \
            portable/_yourshim.o  # add here
```

---

## Path Conversion Patterns

### DOS → UNIX

```c
char *unix = DOSPath2UNIXPath(dos_path);
// "C:\Windows\System32" → "/system/bin"
// ".\file.txt" → "./file.txt"
// "..\dir" → "../dir"
```

### UNIX → DOS

```c
char *dos = UNIXPath2DOSPath(unix_path);
// "/system/bin" → "C:\Windows\System32"
// "./file.txt" → ".\file.txt"
```

### Split Path Components

```c
char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
_splitpath(dos_path, drive, dir, fname, ext);
```

---

## Error Handling

### Set Win32 Error from errno

```c
#include "portable/_error.c"

DWORD WINAPI SetLastErrno(void)
{
    switch (errno) {
        case ENOENT:  return SetLastError(ERROR_FILE_NOT_FOUND);
        case EACCES:  return SetLastError(ERROR_ACCESS_DENIED);
        case EBADF:   return SetLastError(ERROR_INVALID_HANDLE);
        case ENOMEM:  return SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        case EINVAL:  return SetLastError(ERROR_INVALID_PARAMETER);
        case EEXIST:  return SetLastError(ERROR_ALREADY_EXISTS);
        case ENOSPC:  return SetLastError(ERROR_DISK_FULL);
        default:      return SetLastError(ERROR_GEN_FAILURE);
    }
}
```

### Get Win32 Error

```c
DWORD err = GetLastError();
// Use in error messages
cmdutil_Complain(IDS_ERROR_GENERAL, function_name, arg);
```

---

## Testing New Code

### Unit Test Template

```bash
#!/bash
# tests/test_yourcmd.sh
set -e

./cmd.exe /c "yourcmd /s testfile.txt" | grep -q "expected"
echo "✅ yourcmd test passed"
```

### Shim Test Template

```c
// tests/test_yourshim.c
#include "cmd.h"
int main() {
    TCHAR buf[MAX_PATH];
    BOOL r = YourWin32API(param, buf, MAX_PATH);
    assert(r == TRUE);
    assert(_tcscmp(buf, expected) == 0);
    return 0;
}
```

---

## Debugging Tips

### Enable Debug Logs

```c
#define DEBUG 1
#include "cmd.h"

// In your code:
DEBUG((CTGRP, LVL, "YourShim: param=%s", param));
```

### Compile with Debug

```bash
make DEBUG=1  # -g -O0 -DDEBUG
gdb ./cmd.exe
```

### Trace Syscalls

```bash
strace -f -e trace=openat,read,write ./cmd.exe /c "yourcmd file.txt"
```

---

## Code Review Checklist

- [ ] No memory leaks (all `malloc` paired with `free`)
- [ ] Error paths clean up resources
- [ ] DOS/UNIX path conversion correct
- [ ] Win32 error codes mapped properly
- [ ] Thread-safe (no globals without locks)
- [ ] No buffer overflows (use `strncpy`, `snprintf`)
- [ ] Handles both `/` and `\` in paths
- [ ] Wildcards work with `FindFirstFile` shim
- [ ] Help strings added to `cmdmsg.mc`
- [ ] Tests added and passing