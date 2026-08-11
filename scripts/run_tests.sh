#!/bin/bash
# run_tests.sh - Full test suite

set -e

CMD="./cmd.exe"
PASS=0
FAIL=0

run_test() {
    local name="$1"
    local cmd="$2"
    local expected="$3"
    
    echo -n "Testing $name... "
    if eval "$CMD /c \"$cmd\"" 2>&1 | grep -q "$expected"; then
        echo "✅ PASS"
        ((PASS++)) || true
    else
        echo "❌ FAIL"
        echo "  Command: $cmd"
        echo "  Expected: $expected"
        ((FAIL++)) || true
    fi
}

echo "=== termux-cmd Test Suite ==="
echo

# Core builtins
run_test "ver" "ver" "Microsoft Windows"
run_test "echo" "echo hello" "hello"
run_test "dir" "dir" "Volume in drive"
run_test "cd" "cd / && pwd" "/"
run_test "pwd" "pwd" ""
run_test "type" "type cmd.exe 2>/dev/null | head -1" "ELF"
run_test "copy" "copy cmd.exe test_copy.exe && test -f test_copy.exe && echo OK" "OK"
run_test "del" "del test_copy.exe && test ! -f test_copy.exe && echo OK" "OK"
run_test "ren" "ren cmd.exe cmd_ren.exe && test -f cmd_ren.exe && echo OK" "OK"
run_test "ren back" "ren cmd_ren.exe cmd.exe && test -f cmd.exe && echo OK" "OK"
run_test "md" "md testdir && test -d testdir && echo OK" "OK"
run_test "rd" "rd testdir && test ! -d testdir && echo OK" "OK"
run_test "copy concat" "echo a > a.txt && echo b > b.txt && copy a.txt+b.txt c.txt && grep -q 'ab' c.txt && echo OK" "OK"
run_test "attrib" "attrib +r cmd.exe && attrib cmd.exe | grep -q R && attrib -r cmd.exe" "R"
run_test "set" "set TESTVAR=hello && set TESTVAR | grep -q TESTVAR=hello" "TESTVAR=hello"
run_test "set /A" "set /A RESULT=5+3 && set RESULT | grep -q RESULT=8" "RESULT=8"
run_test "if exist" "if exist cmd.exe echo FOUND" "FOUND"
run_test "if not exist" "if not exist nonexistent.txt echo MISSING" "MISSING"
run_test "for files" "for %f in (cmd.exe) do @echo %f" "cmd.exe"
run_test "for /L" "for /L %i in (1,1,3) do @echo %i" "1"
run_test "goto" "goto :label && echo SKIPPED :label && echo OK" "OK"
run_test "call" "call :sub && echo BACK :sub && echo SUB" "SUB"
run_test "shift" "shift /1 && echo SHIFTED" "SHIFTED"
run_test "date /T" "date /T" ""
run_test "time /T" "time /T" ""
run_test "vol" "vol" "Volume in drive"
run_test "path" "path" ""
run_test "cls" "cls" ""  # just verify no crash
run_test "title" "title TestTitle" ""
run_test "prompt" "prompt $P$G" ""
run_test "redir out" "echo test > test_redir.txt && cat test_redir.txt" "test"
run_test "redir append" "echo a > test_apnd.txt && echo b >> test_apnd.txt && cat test_apnd.txt" "a"
run_test "pipe" "echo hello | find \"hello\"" "hello"
run_test "wildcard *" "dir *.exe" "cmd.exe"
run_test "wildcard ?" "dir cm?.exe" "cmd.exe"
run_test "if errorlevel" "cmd /c \"exit /b 1\" && if errorlevel 1 echo ERROR" "ERROR"
run_test "if defined" "set VAR=1 && if defined VAR echo DEFINED" "DEFINED"
run_test "if string" "if \"a\"==\"a\" echo MATCH" "MATCH"
run_test "for /R" "for /R %f in (cmd.exe) do @echo %f" "cmd.exe"
run_test "for /D" "for /D %d in (*) do @echo %d" "."
run_test "for /F" "for /F %i in ('echo a b c') do @echo %i" "a"
run_test "subroutine" "call :sub && echo BACK :sub && echo SUB" "SUB"
run_test "exit /b" "cmd /c \"exit /b 42\" && echo CODE=%ERRORLEVEL%" "CODE=42"
run_test "exit" "cmd /c \"exit\"" ""
run_test "rem" "rem comment && echo OK" "OK"
run_test "::" ":: comment && echo OK" "OK"

# Cleanup
rm -f a.txt b.txt c.txt testdir test_redir.txt test_apnd.txt

echo
echo "=== Results: $PASS passed, $FAIL failed ==="
[ $FAIL -eq 0 ] && exit 0 || exit 1