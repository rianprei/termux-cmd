#!/bin/bash
# run_tests.sh - Full test suite (internal commands only; external programs
# are not supported by the port, so tests must not depend on cat/grep/head/etc)

set -e

CMD="./cmd.exe"
PASS=0
FAIL=0

# Clean up leftovers from previous runs (bash-side, before cmd starts)
rm -rf testdir test_copy.exe test_ren.exe test_ren2.exe test_redir.txt \
       test_apnd.txt a.txt b.txt c.txt nope.txt out_test.txt

run_test() {
    local name="$1"
    local cmd="$2"
    local expected="$3"
    
    echo -n "Testing $name... "
    if eval "$CMD /c \"$cmd\"" 2>&1 | grep -q "$expected"; then
        echo "PASS"
        ((PASS++)) || true
    else
        echo "FAIL"
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
run_test "cd" "cd && echo OK" "C:"
run_test "type text" "echo hello > t.txt && type t.txt" "hello"
run_test "type binary" "type cmd.exe" "ELF"
run_test "copy" "copy cmd.exe test_copy.exe && echo OK" "OK"
run_test "del" "del test_copy.exe && echo OK" "OK"
run_test "ren" "copy cmd.exe test_ren.exe && ren test_ren.exe test_ren2.exe && echo OK" "OK"
run_test "ren back" "ren test_ren2.exe test_ren.exe && echo OK" "OK"
run_test "md" "md testdir && echo OK" "OK"
run_test "rd" "rd testdir && echo OK" "OK"
run_test "copy concat" "echo a > a.txt && echo b > b.txt && copy a.txt+b.txt c.txt && type c.txt" "b"
run_test "set" "set TESTVAR=hello && set TESTVAR" "TESTVAR=hello"
run_test "set /A" "set /A RESULT=5+3 && set RESULT" "RESULT=8"
run_test "if exist" "if exist cmd.exe echo FOUND" "FOUND"
run_test "if not exist" "if not exist nonexistent.txt echo MISSING" "MISSING"
run_test "if defined" "set VAR=1 && if defined VAR echo DEFINED" "DEFINED"
run_test "if string" "if \"a\"==\"a\" echo MATCH" "MATCH"
run_test "for files" "for %f in (cmd.exe) do @echo %f" "cmd.exe"
run_test "for /L" "for /L %i in (1,1,3) do @echo %i" "1"
run_test "for /R" "for /R %f in (cmd.exe) do @echo %f" "cmd.exe"
run_test "for /D" "for /D %d in (*) do @echo %d" "."
run_test "for /F" "for /F %i in ('echo a b c') do @echo %i" "a"
run_test "time /T" "time /T" ""
run_test "vol" "vol" "Volume in drive"
run_test "cls" "cls && echo OK" "OK"
run_test "title" "title TestTitle && echo OK" "OK"
run_test "prompt" "prompt \$P\$G && echo OK" "OK"
run_test "redir out" "echo test > test_redir.txt && type test_redir.txt" "test"
run_test "redir append" "echo a > test_apnd.txt && echo b >> test_apnd.txt && type test_apnd.txt" "a"
run_test "wildcard *" "dir *.exe" "cmd.exe"
run_test "wildcard ?" "dir cm?.exe" "cmd.exe"
run_test "exit" "echo before && exit 5" "before"

# Cleanup
rm -rf testdir test_copy.exe test_ren.exe test_ren2.exe test_redir.txt \
       test_apnd.txt a.txt b.txt c.txt nope.txt t.txt out_test.txt

echo
echo "=== Results: $PASS passed, $FAIL failed ==="
[ $FAIL -eq 0 ] && exit 0 || exit 1
