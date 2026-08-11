# Batch Scripting Guide

## Overview

`termux-cmd` supports full Windows batch scripting (`.bat`, `.cmd`) with the same syntax as Windows Server 2003 `cmd.exe`.

---

## Basic Structure

```batch
@echo off
rem This is a comment
echo Hello World
pause
```

---

## Variables

### Set/Unset

```batch
set VAR=value
set VAR=        rem unsets
set /A RESULT=5+3*2
set /P INPUT=Prompt: 
```

### Expansion

```batch
echo %VAR%           rem immediate expansion
echo %%VAR%%         rem literal %VAR%
setlocal EnableDelayedExpansion
echo !VAR!           rem delayed expansion (inside blocks)
```

---

## Control Flow

### If

```batch
if exist file.txt echo Found
if not exist file.txt echo Missing
if %ERRORLEVEL% neq 0 echo Error
if "%VAR%"=="value" echo Match
if defined VAR echo Defined
if "%VAR%"=="" echo Empty

if %A% gtr %B% (
    echo A greater
) else (
    echo B greater or equal
)
```

### For

```batch
rem Files
for %%f in (*.txt) do echo %%f

rem Recursive
for /R %%f in (*.log) do del %%f

rem Directories only
for /D %%d in (*) do echo Dir: %%d

rem Numeric loop
for /L %%i in (1,1,10) do echo %%i

rem File parsing
for /F "tokens=1,2 delims=," %%a in (data.csv) do echo %%a %%b

rem String parsing
for /F "tokens=1-3" %%a in ("one two three") do echo %%a %%b %%c

rem Command output
for /F %%i in ('dir /b *.txt') do echo %%i
```

### Goto

```batch
goto :label
:label
echo Here

if errorlevel 1 goto :error
echo Success
goto :end

:error
echo Failed
:end
```

---

## Subroutines

```batch
call :subroutine arg1 arg2
echo Back from sub
goto :eof

:subroutine
echo Arg1=%1 Arg2=%2
exit /b 0
```

---

## Arguments

```batch
%0  rem script name
%1  rem first arg
%*  rem all args
%~1 rem remove quotes
%~f1 rem full path
%~d1 rem drive
%~p1 rem path
%~n1 rem filename
%~x1 rem extension
```

---

## Error Handling

```batch
command || echo Failed
command && echo Success

if %ERRORLEVEL% neq 0 (
    echo Error %ERRORLEVEL%
    exit /b %ERRORLEVEL%
)

rem In subroutines
exit /b 1  rem return error code
```

---

## Redirection

```batch
command > file.txt          rem stdout overwrite
command >> file.txt         rem stdout append
command < input.txt         rem stdin from file
command 2> errors.txt       rem stderr to file
command 2>&1                rem stderr to stdout
command >nul 2>&1           rem silence all
command | command           rem pipe
```

---

## Practical Examples

### Backup Script

```batch
@echo off
set SRC=C:\Data
set DST=D:\Backup\%DATE:~-4,4%%DATE:~-7,2%%DATE:~-10,2%
mkdir %DST% 2>nul
xcopy %SRC% %DST% /E /H /Y /I
echo Backup complete to %DST%
```

### Loop with Counter

```batch
@echo off
setlocal EnableDelayedExpansion
set COUNT=0
for %%f in (*.txt) do (
    set /A COUNT+=1
    ren "%%f" "file_!COUNT!%%~xf"
)
echo Renamed %COUNT% files
```

### Find and Process

```batch
@echo off
for /R %%f in (*.log) do (
    findstr "ERROR" "%%f" >nul && (
        echo Errors in %%f
        type "%%f"
    )
)
```

### Menu

```batch
@echo off
:menu
cls
echo 1. Backup
echo 2. Restore
echo 3. Exit
set /P CHOICE=Select:
if "%CHOICE%"=="1" goto backup
if "%CHOICE%"=="2" goto restore
if "%CHOICE%"=="3" goto :eof
goto menu

:backup
echo Backing up...
goto menu

:restore
echo Restoring...
goto menu
```

---

## Differences from Windows CMD

| Feature | termux-cmd | Windows CMD |
|---------|------------|-------------|
| Drive letters | `C:\` → `/` | Native |
| UNC paths | Stub only | Full |
| External EXE | Not supported | Native |
| Registry | Not available | Full |
| Services | Not available | `net start` |
| Unicode | Partial (UTF-8) | Full UTF-16 |

---

## Debugging

```batch
@echo on          rem echo commands
setlocal EnableDelayedExpansion
echo DEBUG: VAR=%VAR%
pause
```

---

## Best Practices

1. **Always** `@echo off` at top
2. **Use** `setlocal` / `endlocal` for isolation
3. **Quote** paths with spaces: `"%PATH%"`
3. **Check** `ERRORLEVEL` after external commands
4. **Use** `exit /b` not `exit` in subroutines
4. **Avoid** `goto` spaghetti — use `call :sub`