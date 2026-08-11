#include "compat.h"
#include <unistd.h>
#include <termios.h>

BOOL WINAPI CreateProcess(LPCTSTR a, LPTSTR cmd, LPVOID pa, LPVOID ta, BOOL inh,
    DWORD flags, LPVOID env, LPCTSTR dir, LPSTARTUPINFO si, LPPROCESS_INFORMATION pi)
{
    (void)a; (void)pa; (void)ta; (void)inh; (void)flags; (void)env; (void)si;
    if (!cmd || !pi) return FALSE;
    const char *sh = getenv("SHELL"); if (!sh) sh = "/bin/sh";
    char *argv[] = {(char*)"/bin/sh", (char*)"-c", cmd, NULL};
    pid_t pid = fork();
    if (pid == 0) {
        if (dir) chdir(dir);
        execvp("sh", argv);
        _exit(127);
    }
    pi->hProcess = (HANDLE)(long)pid;
    pi->dwProcessId = (DWORD)pid;
    return pid > 0;
}

BOOL WINAPI FillConsoleOutputAttribute(FILE *h, WORD attr, DWORD n, COORD c, LPDWORD wr)
{
    (void)h; (void)attr; (void)n; (void)c; if (wr) *wr = 0; return TRUE;
}

BOOL WINAPI FillConsoleOutputCharacterA(FILE *h, TCHAR ch, DWORD n, COORD c, LPDWORD wr)
{
    (void)h; (void)ch; (void)n; (void)c; if (wr) *wr = 0; return TRUE;
}

UINT WINAPI GetConsoleOutputCP(void)
{
    return 65001;
}

BOOL WINAPI GetConsoleScreenBufferInfo(FILE *h, PCONSOLE_SCREEN_BUFFER_INFO info)
{
    (void)h;
    if (!info) return FALSE;
    memset(info, 0, sizeof(*info));
    info->dwSize.X = 80; info->dwSize.Y = 24;
    info->dwMaximumWindowSize.X = 80; info->dwMaximumWindowSize.Y = 24;
    info->wAttributes = 7;
    return TRUE;
}

BOOL WINAPI GetCPInfo(UINT cp, LPCPINFO info)
{
    (void)cp;
    if (!info) return FALSE;
    memset(info, 0, sizeof(*info));
    info->MaxCharSize = 1;
    info->DefaultChar[0] = '?';
    return TRUE;
}

BOOL WINAPI ReadConsoleInputA(FILE *h, LPVOID buf, DWORD n, LPDWORD rd)
{
    (void)buf; (void)n; if (rd) *rd = 0; return TRUE;
}

BOOL WINAPI ReadConsoleOutputCharacterA(FILE *h, LPTSTR s, DWORD n, COORD c, LPDWORD rd)
{
    (void)h; (void)c; if (rd) *rd = 0;
    if (s && n) s[0] = 0;
    return TRUE;
}

BOOL WINAPI ScrollConsoleScreenBuffer(FILE *h, SMALL_RECT *src, SMALL_RECT *clip, COORD dest, CHAR_INFO *fill)
{
    (void)h; (void)src; (void)clip; (void)dest; (void)fill;
    return TRUE;
}

BOOL WINAPI SetConsoleCursorInfo(FILE *h, LPVOID info)
{
    (void)h; (void)info; return TRUE;
}

BOOL WINAPI SetConsoleCursorPosition(FILE *h, COORD c)
{
    (void)h; (void)c; return TRUE;
}

BOOL WINAPI SetConsoleMode(FILE *h, DWORD mode)
{
    int fd = fileno(h);
    struct termios t;
    if (tcgetattr(fd, &t) == 0) {
        if (mode & ENABLE_ECHO_INPUT) t.c_lflag |= ECHO; else t.c_lflag &= ~ECHO;
        if (mode & ENABLE_LINE_INPUT) t.c_lflag |= ICANON; else t.c_lflag &= ~ICANON;
        tcsetattr(fd, TCSANOW, &t);
    }
    return TRUE;
}

BOOL WINAPI SetConsoleTextAttribute(FILE *h, WORD attr)
{
    (void)h; (void)attr; return TRUE;
}

BOOL WINAPI WriteConsoleOutputCharacterA(FILE *h, LPCTSTR s, DWORD n, COORD c, LPDWORD wr)
{
    (void)c;
    fwrite(s, 1, n, h);
    if (wr) *wr = n;
    return TRUE;
}

int SizeOfHalfWidthString(TCHAR *pwch)
{
    return pwch ? (int)strlen(pwch) : 0;
}