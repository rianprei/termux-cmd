# Command Reference

Complete list of supported commands with syntax and examples.

---

## Navigation

### `cd` / `chdir`

Change current directory.

```cmd
cd [drive:][path]
cd ..
cd \
cd C:\Windows
```

**Options**: None

**Notes**: 
- `cd ..` goes to parent directory
- `cd \` goes to root of current drive
- Drive letter changes current drive AND directory

### `pwd`

Print working directory.

```cmd
pwd
```

---

## Filesystem

### `dir`

List directory contents.

```cmd
dir [drive:][path][filename] [/A[[:]attributes]] [/B] [/C] [/D] [/L] [/N] [/O[[:]sortorder]] [/P] [/Q] [/S] [/T[[:]timefield]] [/W] [/X] [/4]
```

**Options**:
| Option | Description |
|--------|-------------|
| `/A` | Filter by attributes (D=dir, H=hidden, S=system, R=readonly, A=archive) |
| `/B` | Bare format (no header/summary) |
| `/S` | Recurse subdirectories |
| `/W` | Wide format |
| `/O:N` | Sort by name (default) |
| `/O:S` | Sort by size |
| `/O:E` | Sort by extension |
| `/O:D` | Sort by date/time |
| `/O:-` | Reverse sort |
| `/T:C` | Show creation time |
| `/T:A` | Show last access time |
| `/T:W` | Show last write time (default) |

**Examples**:
```cmd
dir
dir /w
dir /b /s *.txt
dir /a:h /s
dir /o:d /t:w
```

### `type`

Display file contents.

```cmd
type [drive:][path]filename
```

**Example**:
```cmd
type C:\Windows\win.ini
type readme.txt
```

### `copy`

Copy files.

```cmd
copy [/D] [/V] [/N] [/Y | /-Y] [/Z] [/A | /B] source [/A | /B] [+ source [/A | /B] [+ ...]] [destination [/A | /B]]
```

**Options**:
| Option | Description |
|--------|-------------|
| `/Y` | Suppress overwrite prompt |
| `/-Y` | Prompt on overwrite |
| `/V` | Verify after copy |
| `/B` | Binary mode |
| `/A` | ASCII mode (text) |
| `+` | Concatenate files |

**Examples**:
```cmd
copy file1.txt file2.txt
copy *.txt combined.txt
copy /b image1.jpg + image2.jpg combined.jpg
copy /y source\* dest\
```

### `del` / `erase`

Delete files.

```cmd
del [/P] [/F] [/S] [/Q] [/A[[:]attributes]] names
```

**Options**:
| Option | Description |
|--------|-------------|
| `/P` | Prompt before delete |
| `/F` | Force delete readonly |
| `/S` | Delete from subdirectories |
| `/Q` | Quiet (no prompt) |
| `/A` | Filter by attributes |

**Examples**:
```cmd
del temp.txt
del /s /q *.tmp
del /p /f readonly.txt
```

### `ren` / `rename`

Rename files.

```cmd
ren [drive:][path]filename1 filename2
```

**Notes**:
- Cannot move across directories (use `move`)
- Wildcards supported for multiple files

```cmd
ren *.txt *.bak
ren oldname.txt newname.txt
```

### `move`

Move files.

```cmd
move [/Y | /-Y] [drive:][path]filename1[,...] destination
```

**Options**:
| Option | Description |
|--------|-------------|
| `/Y` | Suppress overwrite prompt |
| `/-Y` | Prompt on overwrite |

**Examples**:
```cmd
move file.txt C:\Backup\
move *.log logs\
move /y oldname.txt newname.txt
```

### `md` / `mkdir`

Create directory.

```cmd
md [drive:]path
```

```cmd
md newdir
md C:\Projects\NewFolder
```

### `rd` / `rmdir`

Remove directory.

```cmd
rd [/S] [/Q] [drive:]path
```

**Options**:
| Option | Description |
|--------|-------------|
| `/S` | Remove tree (dir + contents) |
| `/Q` | Quiet (no prompt with /S) |

```cmd
rd emptydir
rd /s /q fulldir
```

---

## Attributes

### `attrib`

Display/change file attributes.

```cmd
attrib [+R|-R] [+A|-A] [+S|-S] [+H|-H] [/S] [/D] [drive:][path]filename
```

**Attributes**:
| Flag | Meaning |
|------|---------|
| `R` | Read-only |
| `A` | Archive |
| `S` | System |
| `H` | Hidden |

**Options**:
| Option | Description |
|--------|-------------|
| `/S` | Process subdirectories |
| `/D` | Apply to directories too |

**Examples**:
```cmd
attrib +r file.txt
attrib -h -s /s /d *
attrib +a *.txt
```

---

## Environment

### `set`

Display/set/remove environment variables.

```cmd
set [variable=[string]]
set /A expression
set /P variable=[promptString]
```

**Options**:
| Option | Description |
|--------|-------------|
| `/A` | Evaluate arithmetic expression |
| `/P` | Prompt for input |

**Examples**:
```cmd
set
set MYVAR=hello
set /A RESULT=5+3
set /P NAME=Enter name:
set MYVAR=  (removes variable)
```

### `path`

Display/set search path for executables.

```cmd
path [ [drive:]path[;...] ]
path ;
```

```cmd
path
path C:\bin;C:\tools
path ;  (clears path)
```

### `ver`

Display Windows version.

```cmd
ver
```

### `vol`

Display disk volume label and serial number.

```cmd
vol [drive:]
```

---

## Batch/Control Flow

### `if`

Conditional execution.

```cmd
if [not] ERRORLEVEL number command
if [not] string1==string2 command
if [not] EXIST filename command
if [not] DEFINED variable command
if [not] CMDEXTVERSION number command
```

**Examples**:
```cmd
if exist file.txt echo Found
if %ERRORLEVEL% neq 0 echo Error
if "%VAR%"=="value" echo Match
if defined VAR echo Defined
```

### `for`

Loop over files/strings/numbers.

```cmd
for %variable in (set) do command [command-parameters]
for /R [[drive:]path] %variable in (set) do command
for /D %variable in (set) do command
for /L %variable in (start,step,end) do command
for /F ["options"] %variable in (filenameset) do command
for /F ["options"] %variable in ("string") do command
for /F ["options"] %variable in ('command') do command
```

**Examples**:
```cmd
for %f in (*.txt) do echo %f
for /r %f in (*.log) do del %f
for /l %i in (1,1,10) do echo %i
for /f "tokens=1,2 delims=," %a in (data.csv) do echo %a %b
```

### `goto`

Jump to label.

```cmd
goto label
:label
```

```cmd
if error goto :error_handler
echo Success
:error_handler
echo Failed
```

### `call`

Call another batch file or label.

```cmd
call [drive:][path]filename [batch-parameters]
call :label arguments
```

### `shift`

Shift batch parameters.

```cmd
shift [/n]
```

### `pause`

Pause execution.

```cmd
pause
```

### `rem`

Comment/remark.

```cmd
rem This is a comment
:: Also a comment
```

---

## Console

### `cls`

Clear screen.

```cmd
cls
```

### `echo`

Display message or toggle echo.

```cmd
echo [on|off]
echo [message]
```

```cmd
echo off
echo Hello World
echo.
```

### `title`

Set console window title.

```cmd
title [string]
```

### `prompt`

Change command prompt.

```cmd
prompt [string]
```

**Special Codes**:
| Code | Expands To |
|------|------------|
| `$P` | Current drive/path |
| `$G` | `>` |
| `$L` | `<` |
| `$B` | `|` |
| `$C` | `(` |
| `$F` | `)` |
| `$Q` | `=` |
| `$S` | space |
| `$T` | Current time |
| `$D` | Current date |
| `$_` | Newline |
| `$E` | Escape (ASCII 27) |
| `$A` | `&` |
| `$V` | Windows version |
| `$$` | `$` |

```cmd
prompt $P$G
prompt $D $T $_ $P$G
```

---

## Date/Time

### `date`

Display/set date.

```cmd
date [/T | date]
```

```cmd
date
date 12-31-2026
date /T
```

### `time`

Display/set time.

```cmd
time [/T | time]
```

```cmd
time
time 14:30:00
time /T
```

---

## Redirection & Pipes

| Syntax | Description |
|--------|-------------|
| `command > file` | Stdout to file (overwrite) |
| `command >> file` | Stdout to file (append) |
| `command < file` | Stdin from file |
| `command 2> file` | Stderr to file |
| `command 2>&1` | Stderr to stdout |
| `command | command` | Pipe stdout to stdin |

**Examples**:
```cmd
dir > listing.txt
type file.txt | find "search"
command > output.txt 2>&1
echo hello > file.txt
```

---

## Wildcards

| Pattern | Matches |
|---------|---------|
| `*` | Any characters (including none) |
| `?` | Single character |
| `[abc]` | Single char in set |
| `[a-z]` | Single char in range |

```cmd
dir *.txt
del file?.tmp
copy [abc]*.log dest\
```

---

## Exit Codes

| Code | Meaning |
|------|---------|
| 0 | Success |
| 1 | General error |
| 2 | File not found |
| 3 | Path not found |
| 5 | Access denied |
| 255 | Syntax error |

```cmd
echo %ERRORLEVEL%
```

---

## Help

```cmd
help [command]
command /?
```

```cmd
help
help dir
dir /?
```