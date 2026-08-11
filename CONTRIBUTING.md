# Contributing to termux-cmd

Thank you for your interest in contributing! This document outlines the process and guidelines for contributing to termux-cmd.

## 🎯 Ways to Contribute

- **Bug Reports** — Found a crash or incorrect behavior? Open an issue.
- **Feature Requests** — Missing a command or option? Request it.
- **Code Contributions** — Fix bugs, add commands, improve shims.
- **Documentation** — Improve docs, add examples, fix typos.
- **Testing** — Run tests on different devices/Android versions.

---

## 🚀 Getting Started

### Prerequisites

- Termux (latest)
- `pkg install clang make git python3`
- Fork the repository

### Development Setup

```bash
git clone https://github.com/rianprei/termux-cmd.git
cd termux-cmd
make clean && make
./cmd.exe  # test it works
```

---

## 📝 Code Style

### C Code (K&R Style)

```c
/* Good */
int my_function(int arg1, char *arg2)
{
    if (arg1 > 0) {
        do_something(arg2);
        return SUCCESS;
    }
    return FAILURE;
}

/* Avoid */
// int my_function(int arg1, char *arg2) { if(arg1>0) return do_something(arg2), SUCCESS; else return FAILURE; }
```

### Rules

- **Indentation**: Tabs = 4 spaces
- **Braces**: Opening brace on new line (K&R)
- **Line length**: ≤ 100 chars
- **Naming**: `snake_case` for functions/vars, `PascalCase` for types
- **Comments**: Only for complex logic, not obvious code

### Commit Messages

```
<type>(<scope>): <subject>

<body>

<footer>
```

Types: `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`

Example:
```
fix(shim): handle forward slash in MoveFile

MoveFile shim was using original DOS path instead of converted
UNIX path for rename(2) syscall.

Fixes #42
```

---

## 🔧 Adding a New Command

### 1. Prototype in `cmdproto.h`

```c
int cmdexec_CmdMycmd(TCHAR *lpName, TCHAR *lpArgs);
```

### 2. Register in `cmdexec.c`

```c
Command aAllCommands[] = {
    // ... existing commands ...
    { TEXT("MYCMD"),    IDS_HELP_CMD_MYCMD,    IDS_HELP_EXT_MYCMD,    cmdexec_CmdMycmd    },
};
```

### 3. Implement in `cmdexec.c`

```c
int cmdexec_CmdMycmd(TCHAR *lpName, TCHAR *lpArgs)
{
    // Parse args with cmdutil_ParseCommandParameters
    // Use portable/ shims for file ops
    // Return CMD_SUCCESS or CMD_ERROR
    return CMD_SUCCESS;
}
```

### 4. Add Help Strings to `cmdmsg.mc`

```
MessageId=3000
SymbolicName=IDS_HELP_CMD_MYCMD
Language=Portuguese
MYCMD - Description here.
.

MessageId=3001
SymbolicName=IDS_HELP_EXT_MYCMD
Language=Portuguese
MYCMD [options] [arguments]
Description...
.
```

### 5. Regenerate Messages

```bash
python3 parsemsg.py
make clean && make
```

### 5. Add Tests

Create `tests/test_mycmd.sh` and ensure it passes.

---

## 🧪 Testing

### Run All Tests

```bash
./scripts/run_tests.sh
```

### Test Categories

| Script | Purpose |
|--------|---------|
| `test_builtins.sh` | Core commands (dir, cd, copy, etc.) |
| `test_batch.sh` | Batch scripting (.bat/.cmd) |
| `test_paths.sh` | Path translation DOS↔UNIX |
| `test_wildcards.sh` | Glob patterns, recursion |
| `test_shims.sh` | Portable layer correctness |

### Adding a Test

```bash
# tests/test_mycmd.sh
#!/bin/bash
set -e
./cmd.exe /c "mycmd arg1 arg2" | grep -q "expected output"
echo "✅ mycmd test passed"
```

---

## 📦 Pull Request Process

1. **Create branch**: `git checkout -b feat/mycmd`
2. **Commit** with proper messages
3. **Push**: `git push origin feat/mycmd`
4. **Open PR** with:
   - Clear description
   - Related issue number
   - Test results
   - Screenshots (if UI)

### PR Requirements

- [ ] All tests pass (`./scripts/run_tests.sh`)
- [ ] Code follows style guide
- [ ] Documentation updated
- [ ] CHANGELOG.md updated
- [ ] No warnings on `make` (clean build)

---

## 🐛 Bug Reports

Use the **Bug Report** template on GitHub Issues. Include:

- Termux version (`pkg list-all termux`)
- Android version
- Device architecture (`uname -m`)
- Command that fails
- Expected vs actual behavior
- Minimal reproduction steps
- Full error output (if any)

---

## 💡 Feature Requests

Use the **Feature Request** template. Explain:

- What problem it solves
- How it should work
- Windows CMD behavior (if applicable)
- Implementation ideas

---

## 📞 Questions?

- GitHub Discussions for general questions
- Issues for bugs/features
- Email: your@email.com for security issues

---

Thank you for contributing! 🎉