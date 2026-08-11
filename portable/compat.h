#ifndef COMPAT_H_
#define COMPAT_H_

// Oracle says this code is fine to copy from MSDN because it's just APIs...

#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <wchar.h>
#include <stddef.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define WIN95_CMD
#define PORTABLE_CMD

#define MAX_PATH PATH_MAX

#define CONST const

#define O_BINARY 0
#define _O_APPEND O_APPEND
#define _O_BINARY O_BINARY

#define INFINITE  0xFFFFFFFF
#define CONTROL_C_EXIT   ((DWORD)0xC000013A)
#define CTRL_C_EVENT 0
#define CTRL_BREAK_EVENT 1

#if INTPTR_MAX == INT64_MAX
#define _ARCH64BIT
#elif INTPTR_MAX == INT32_MAX
#define _ARCH32BIT
#else
#error Unknown pointer size or missing size macros!

typedef void* PIMAGE_NT_HEADERS;
typedef void* PPEB;
typedef void* PEB;
typedef void* PEB_STRUCT;

#endif

// See: https://msdn.microsoft.com/en-gb/library/windows/desktop/aa383751(v=vs.85).aspx
typedef unsigned char BYTE;
typedef unsigned char *PBYTE;
typedef char TCHAR, *LPTCH;
typedef char CHAR;
typedef char CCHAR;
typedef wchar_t WCHAR;
typedef WCHAR *LPWSTR;
typedef CONST WCHAR *LPCWSTR;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef short SHORT;
typedef CHAR *PCHAR;
typedef CONST CHAR *LPCSTR;
typedef CONST CHAR *LPCTSTR;
typedef uint16_t WORD;
typedef int32_t LONG;
typedef LONG *PLONG;
typedef uint32_t ULONG, UINT;
typedef ULONG *PULONG;
#if defined(_ARCH64BIT)
 typedef uint64_t ULONG_PTR;
 typedef int64_t LONG_PTR;
#else
 typedef uint32_t ULONG_PTR;
 typedef int32_t LONG_PTR;


#endif
typedef ULONG_PTR *PULONG_PTR;

#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000
#define _open_osfhandle(handle, flags) (handle)
#define IsReparseTagNameSurrogate(tag) FALSE
typedef TCHAR* PTCHAR;
typedef void VOID;
typedef VOID* PVOID;
typedef unsigned long long DWORD_PTR;
#define HandleToUlong(h) ((DWORD)(unsigned long)(h))
typedef CONST VOID* LPCVOID;
typedef unsigned short USHORT;
typedef bool BOOLEAN;
typedef bool BOOL;
typedef BOOL* PBOOL;
typedef BOOL* LPBOOL;
typedef uint32_t DWORD;
typedef DWORD *LPDWORD;
typedef WORD *PWORD;
typedef int64_t LONGLONG;
typedef PVOID HANDLE, *PHANDLE, *LPHANDLE;
typedef HANDLE HINSTANCE, HMODULE;
typedef HANDLE HWND;
typedef HANDLE* PHANDLE;
typedef HANDLE HKEY;
typedef unsigned char BYTE, *LPBYTE;
typedef void *LPVOID;
typedef size_t SIZE_T;

typedef HANDLE HDESK, HWINSTA;
#define SW_SHOWNORMAL 1

typedef uint64_t ULONGLONG;
typedef ULONGLONG *PULONGLONG;

#define FALSE false
#define TRUE true

typedef char *LPSTR;
#ifdef UNICODE
 typedef LPWSTR LPTSTR;
#else
 typedef LPSTR LPTSTR;


#endif

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  };
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
  struct {
    DWORD LowPart;
    DWORD HighPart;
  };
  struct {
    DWORD LowPart;
    DWORD HighPart;
  } u;
  ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms724284(v=vs.85).aspx
typedef struct _FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;


typedef struct _SHELLEXECUTEINFO {
  DWORD     cbSize;
  ULONG     fMask;
  HWND      hwnd;
  LPCTSTR   lpVerb;
  LPCTSTR   lpFile;
  LPCTSTR   lpParameters;
  LPCTSTR   lpDirectory;
  int       nShow;
  HINSTANCE hInstApp;
  LPVOID    lpIDList;
  LPCTSTR   lpClass;
  HKEY      hkeyClass;
  DWORD     dwHotKey;
  union {
    HANDLE hIcon;
    HANDLE hMonitor;
  } DUMMYUNIONNAME;
  HANDLE    hProcess;
} SHELLEXECUTEINFO, *LPSHELLEXECUTEINFO;


// https://msdn.microsoft.com/en-us/library/windows/desktop/ms686331(v=vs.85).aspx
typedef struct _STARTUPINFO {
  DWORD  cb;
  LPTSTR lpReserved;
  LPTSTR lpDesktop;
  LPTSTR lpTitle;
  DWORD  dwX;
  DWORD  dwY;
  DWORD  dwXSize;
  DWORD  dwYSize;
  DWORD  dwXCountChars;
  DWORD  dwYCountChars;
  DWORD  dwFillAttribute;
  DWORD  dwFlags;
  WORD   wShowWindow;
  WORD   cbReserved2;
  LPBYTE lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} STARTUPINFO, *LPSTARTUPINFO;

typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD  dwProcessId;
  DWORD  dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef struct _SECURITY_ATTRIBUTES {
  DWORD  nLength;
  LPVOID lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;


// https://msdn.microsoft.com/en-us/library/windows/desktop/ms724950(v=vs.85).aspx
static inline void FreeEnvironmentStrings(LPVOID p) { (void)p; }
static inline void SetEnvironmentStrings(LPVOID p) { (void)p; }
static inline DWORD GetCurrentThreadId(void) { return 1; }

static inline BOOL NeedCurrentDirectoryForExePath(LPCTSTR p) { (void)p; return FALSE; }
#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)
#define HKEY_CURRENT_USER ((HKEY)0x80000001)
#define REG_NONE 0
#define REG_DWORD 4
typedef HKEY HKEY;
static inline LONG RegOpenKey(HKEY hk, LPCTSTR sub, HKEY *out) { (void)hk; (void)sub; (void)out; return 1; }
#define PHKEY HKEY *
static inline LONG RegEnumKey(HKEY hk, DWORD i, LPTSTR name, DWORD n) { (void)hk; (void)i; (void)name; (void)n; return 1; }
static inline LONG RegQueryValue(HKEY hk, LPCTSTR sub, LPTSTR val, PLONG n) { (void)hk; (void)sub; (void)val; (void)n; return 1; }
static inline LONG RegDeleteKey(HKEY hk, LPCTSTR sub) { (void)hk; (void)sub; return 1; }
static inline LONG RegDeleteValue(HKEY hk, LPCTSTR val) { (void)hk; (void)val; return 1; }
#define REG_SZ 1
static inline LONG RegSetValue(HKEY hk, LPCTSTR sub, DWORD type, LPVOID val, DWORD n) { (void)hk; (void)sub; (void)type; (void)val; (void)n; return 0; }
#define REGSAM DWORD
#define REG_EXPAND_SZ 2
#define MAXIMUM_ALLOWED 0x02000000
#define NTAPI __stdcall
#define PROCESSINFOCLASS int
#define NTQUERYINFORMATIONPROCESS NTSTATUS (*)(HANDLE, int, PVOID, ULONG, PULONG)
#define NTSTATUS LONG
static inline LONG RegSetValueEx(HKEY hk, LPCTSTR valname, DWORD r1, DWORD type, CONST BYTE *data, DWORD cbData) { (void)hk; (void)valname; (void)r1; (void)type; (void)data; (void)cbData; return 0; }
static inline LONG RegCreateKeyEx(HKEY hk, LPCTSTR sub, DWORD r, LPVOID class, DWORD opt, REGSAM sam, LPVOID sa, HKEY *out, LPDWORD disp) {
    (void)hk; (void)sub; (void)r; (void)class; (void)opt; (void)sam; (void)sa; (void)out; (void)disp; return 1;
}
#define SHCNE_ASSOCCHANGED 0x08000000
#define SHCNF_IDLIST 0x00000000
static inline void SHChangeNotify(LONG w, UINT u, LPVOID p1, LPVOID p2) { (void)w; (void)u; (void)p1; (void)p2; }
static inline LONG RegQueryValueEx(HKEY hk, LPCTSTR name, LPDWORD r, LPDWORD t, LPVOID d, LPDWORD n) {
    (void)hk; (void)name; (void)r; (void)t; (void)d; (void)n; return 1;
}
static inline LONG RegCloseKey(HKEY hk) { (void)hk; return 0; }

static inline HWINSTA GetProcessWindowStation(void) { return (HWINSTA)"WinSta0"; }
/* CreateProcess declarado abaixo */

static inline DWORD ExpandEnvironmentStrings(LPCTSTR lpSrc, LPTSTR lpDst, DWORD nSize) {
    (void)lpSrc; (void)nSize;
    if (lpDst && nSize) lpDst[0] = 0;
    return 0;
}

typedef WCHAR *PWSTR;

typedef struct { int dummy; } CRITICAL_SECTION;
typedef CRITICAL_SECTION *LPCRITICAL_SECTION;
static inline void InitializeCriticalSection(LPCRITICAL_SECTION cs) { (void)cs; }
static inline void DeleteCriticalSection(LPCRITICAL_SECTION cs) { (void)cs; }
static inline void EnterCriticalSection(LPCRITICAL_SECTION cs) { (void)cs; }
static inline void LeaveCriticalSection(LPCRITICAL_SECTION cs) { (void)cs; }

static inline long _wtol(LPCWSTR s) {
    char buf[64]; size_t n = wcstombs(buf, s, sizeof(buf) - 1);
    if (n == (size_t)-1) return 0;
    buf[n] = 0;
    return atol(buf);
}

#define CP_ACP 0
#define CP_UTF8 65001

static inline int MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr,
    int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar) {
    (void)CodePage; (void)dwFlags;
    size_t n = mbstowcs(lpWideCharStr, lpMultiByteStr, cchWideChar > 0 ? (size_t)cchWideChar : (size_t)cbMultiByte);
    if (n == (size_t)-1) return 0;
    return (int)n;
}

#define MOVEFILE_REPLACE_EXISTING 1
#define MOVEFILE_COPY_ALLOWED 2

static inline BOOL MoveFileEx(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, DWORD dwFlags) {
    (void)dwFlags;
    if (rename(lpExistingFileName, lpNewFileName) == 0) return TRUE;
    return FALSE;
}

/* decl movida */
BOOL CreateProcess(LPCTSTR lpApplicationName, LPTSTR lpCommandLine, LPVOID lpProcessAttributes, LPVOID lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCTSTR lpCurrentDirectory, LPSTARTUPINFO lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
static inline BOOL CreateProcessAsUser(HANDLE hToken, LPCTSTR lpApplicationName, LPTSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
    LPCTSTR lpCurrentDirectory, LPSTARTUPINFO lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation) {
    (void)hToken; (void)lpProcessAttributes; (void)lpThreadAttributes; (void)bInheritHandles;
    (void)dwCreationFlags; (void)lpEnvironment; (void)lpCurrentDirectory;
    return CreateProcess(lpApplicationName, lpCommandLine, NULL, NULL, bInheritHandles,
        dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}
static inline HDESK GetThreadDesktop(DWORD dwThreadId) { (void)dwThreadId; return (HDESK)"Default"; }
#define leave goto leave
#define UOI_NAME 2
static inline BOOL GetUserObjectInformation(HANDLE h, int idx, LPVOID p, DWORD n, LPDWORD pn) {
    (void)idx;
    const char *s = "Default"; size_t l = strlen(s);
    if (p && n >= (DWORD)l + 1) { memcpy(p, s, l); ((char*)p)[l] = 0; }
    if (pn) *pn = (DWORD)l + 1;
    return TRUE;
}
typedef struct _SYSTEMTIME {
  WORD wYear;
  WORD wMonth;
  WORD wDayOfWeek;
  WORD wDay;
  WORD wHour;
  WORD wMinute;
  WORD wSecond;
  WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms724251(v=vs.85).aspx
#define DUPLICATE_CLOSE_SOURCE 0x00000001

#define WINAPI
#define _CRTAPI1

// https://msdn.microsoft.com/en-us/library/windows/desktop/aa363854(v=vs.85).aspx
typedef DWORD (WINAPI *LPPROGRESS_ROUTINE)(
         LARGE_INTEGER TotalFileSize,
         LARGE_INTEGER TotalBytesTransferred,
         LARGE_INTEGER StreamSize,
         LARGE_INTEGER StreamBytesTransferred,
         DWORD         dwStreamNumber,
         DWORD         dwCallbackReason,
         HANDLE        hSourceFile,
         HANDLE        hDestinationFile,
    	 LPVOID        lpData
);

LPTSTR WINAPI GetCommandLine(void);
VOID WINAPI SetCommandLine(int argc, char **argv);
DWORD WINAPI GetVersion(void);

char *strtolower(char *buf);
char* strtoupper(char* s);

#define _tcslwr strtolower
#define lstrcmpi strcasecmp
#define _tcsstr strstr
#define _tcsrchr strrchr
#define _tcsicmp strcasecmp
#define _tcschr strchr
#define _tcslen strlen
#define _tcscpy strcpy
#define _tcsncpy strncpy
#define _tcscat strcat
#define _tcsncmp strncmp
#define _tcscmp strcmp
#define _tcstol strtol
#define _tcsnicmp strncasecmp
#define _tcsupr strtoupper
#define _istspace isspace
#define _istxdigit isxdigit
#define _istalpha isalpha
#define _istdigit isdigit
#define _totlower tolower
#define _totupper toupper
#define _sntprintf snprintf
#define _stprintf sprintf
#define _stscanf sscanf
#define _vsntprintf vsnprintf 
#define _vsnprintf vsnprintf 
#define TEXT(x) x
#define __TEXT(x) x

#define _getch getchar

#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

#define UNREFERENCED_PARAMETER(p)          ((p)=(p))
#define DBG_UNREFERENCED_PARAMETER(p)      ((p)=(p))
#define DBG_UNREFERENCED_LOCAL_VARIABLE(p) ((p)=(p))

#define _In_
#define _In_opt_
#define _Inout_opt_
#define _Inout_
#define _Reserved_
#define _Out_
#define _Out_opt_
#define IN
#define OUT
#define OPTIONAL

// http://ftp.icpdas.com/pub/beta_version/VHM/wince600/at91sam9g45m10ek_armv4i/cesysgen/ddk/inc/ntintsafe.h
#ifndef UInt32x32To64
#define UInt32x32To64(a, b) ((uint64_t)((unsigned long)(a)) * (uint64_t)((unsigned long)(b)))
#endif // !UInt32x32To64

void _ultoa(unsigned long value, char* string, unsigned char radix);
void _ltoa(long value, char* string, unsigned char radix);

BOOL WINAPI GetConsoleMode(
  _In_  FILE*  hConsoleHandle,
  _Out_ LPDWORD lpMode
);

DWORD WINAPI GetConsoleTitle(
  _Out_ LPTSTR lpConsoleTitle,
  _In_  DWORD  nSize
);

BOOL WINAPI SetConsoleTitle(
  _In_ LPCTSTR lpConsoleTitle
);

void WINAPI DebugBreak(void);


#define INVALID_HANDLE_VALUE NULL
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)


#define FILE_ATTRIBUTE_READONLY 1
#define FILE_ATTRIBUTE_HIDDEN 2
#define FILE_ATTRIBUTE_SYSTEM 4
#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define FILE_ATTRIBUTE_DEVICE 0x40
#define FILE_ATTRIBUTE_ARCHIVE 32
#define FILE_ATTRIBUTE_NORMAL 128
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 8192
#define FILE_ATTRIBUTE_OFFLINE 4096
#define FILE_ATTRIBUTE_TEMPORARY 256
#define FILE_ATTRIBUTE_COMPRESSED 0x800
#define FILE_ATTRIBUTE_REPARSE_POINT 0x400

typedef enum { GetFileExInfoStandard } GET_FILEEX_INFO_LEVELS;

typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
} WIN32_FILE_ATTRIBUTE_DATA;

static inline BOOL GetFileAttributesEx(LPCTSTR lpFileName, GET_FILEEX_INFO_LEVELS lvl, void *lpInfo) {
    (void)lvl;
    struct stat st;
    WIN32_FILE_ATTRIBUTE_DATA *fi = (WIN32_FILE_ATTRIBUTE_DATA *)lpInfo;
    if (stat(lpFileName, &st) != 0) return FALSE;
    memset(fi, 0, sizeof(*fi));
    fi->dwFileAttributes = S_ISDIR(st.st_mode) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
    fi->nFileSizeLow = (DWORD)st.st_size;
    fi->nFileSizeHigh = (DWORD)((unsigned long long)st.st_size >> 32);
    return TRUE;
}

static inline void LocalFree(void *p) { free(p); }
static inline void SetFileApisToOEM(void) { }

#define try if(1)
#define except(...) else
#define __try if(1)
#define __except(...) else
static inline DWORD GetExceptionCode(void) { return 0; }
typedef int32_t INT;
#define KEY_READ 0x20019

static inline LONG RegOpenKeyEx(HKEY hKey, LPCTSTR lpSubKey, DWORD ulOptions, DWORD samDesired, PHKEY phkResult) {
    (void)hKey; (void)lpSubKey; (void)ulOptions; (void)samDesired;
    if (phkResult) *phkResult = (HKEY)0;
    return 2; /* ERROR_FILE_NOT_FOUND: registry never present on Termux */
}

#define RESOURCETYPE_DISK 1
#define ERROR_DEVICE_ALREADY_REMEMBERED 1202
#define ERROR_NOT_CONNECTED 2250

typedef struct _NETRESOURCE {
    DWORD dwType;
    LPTSTR lpLocalName;
    LPTSTR lpRemoteName;
    LPTSTR lpProvider;
} NETRESOURCE, *LPNETRESOURCE;

static inline DWORD WNetAddConnection2(LPNETRESOURCE lpNetResource, LPCTSTR lpPassword, LPCTSTR lpUserName, DWORD dwFlags) {
    (void)lpNetResource; (void)lpPassword; (void)lpUserName; (void)dwFlags;
    return ERROR_NOT_CONNECTED;
}

static inline DWORD WNetCancelConnection2(LPCTSTR lpName, DWORD dwFlags, BOOL fForce) {
    (void)lpName; (void)dwFlags; (void)fForce;
    return 0;
}
static inline DWORD WNetGetConnection(LPCTSTR lpLocalName, LPTSTR lpRemoteName, LPDWORD lpnLength) {
    (void)lpLocalName; (void)lpRemoteName; (void)lpnLength;
    return ERROR_NOT_CONNECTED;
}

#define PROGRESS_CONTINUE 0
#define PROGRESS_CANCEL 1
#define PROGRESS_STOP 2
#define PROGRESS_QUIET 3

// https://msdn.microsoft.com/en-us/library/windows/desktop/aa363858(v=vs.85).aspx
#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE 0x00000004

// https://msdn.microsoft.com/en-us/library/windows/desktop/aa364960(v=vs.85).aspx
#define FILE_TYPE_CHAR 0x0002
#define FILE_TYPE_DISK 0x0001
#define FILE_TYPE_PIPE 0x0003
#define FILE_TYPE_REMOTE 0x8000
#define FILE_TYPE_UNKNOWN 0x0000

// https://msdn.microsoft.com/en-gb/library/windows/desktop/aa364939(v=vs.85).aspx
#define DRIVE_UNKNOWN 0
#define DRIVE_NO_ROOT_DIR 1
#define DRIVE_REMOVABLE 2
#define DRIVE_FIXED 3
#define DRIVE_REMOTE 4
#define DRIVE_CDROM 5
#define DRIVE_RAMDISK 6

// http://www.jbox.dk/sanos/source/include/win32.h.html
#define GENERIC_READ                     0x80000000
#define GENERIC_WRITE                    0x40000000
#define GENERIC_EXECUTE                  0x20000000
#define GENERIC_ALL                      0x10000000

// http://www.jbox.dk/sanos/source/include/win32.h.html
#define CREATE_NEW                       1
#define CREATE_ALWAYS                    2
#define OPEN_EXISTING                    3
#define OPEN_ALWAYS                      4
#define TRUNCATE_EXISTING                5

// http://www.jbox.dk/sanos/source/include/win32.h.html
#define STD_INPUT_HANDLE                 ((DWORD)-10)
#define STD_OUTPUT_HANDLE                ((DWORD)-11)
#define STD_ERROR_HANDLE                 ((DWORD)-12)

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms686033(v=vs.85).aspx
#define ENABLE_PROCESSED_INPUT 0x0001
#define ENABLE_LINE_INPUT 0x0002
#define ENABLE_ECHO_INPUT 0x0004
#define ENABLE_MOUSE_INPUT 0x0010
#define ENABLE_WRAP_AT_EOL_OUTPUT 0x0002
#define ENABLE_PROCESSED_OUTPUT 0x0001

// https://github.com/gasgas4/NT_4.0_SourceCode/blob/84a03f73738328ea66034dca7cda79a857623720/nt4/private/windows/inc/shellapi.w
#define SEE_MASK_HASTITLE       0x00080000       
#define SEE_MASK_FLAG_DDEWAIT   0x00000100                        
#define SEE_MASK_NO_CONSOLE     0x00008000
#define SEE_MASK_NOCLOSEPROCESS 0x00000040

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
#define CREATE_NEW_CONSOLE 0x00000010
#define CREATE_NEW_PROCESS_GROUP 0x00000200
#define CREATE_NO_WINDOW 0x08000000

// https://webcache.googleusercontent.com/search?q=cache:xaaywBK_sCkJ:https://sourceforge.net/u/cstrauss/w32api/ci/f3077014e6186628344d580460bfafe4d3b52c9d/tree/include/winbase.h%3Fformat%3Draw+&cd=1&hl=en&ct=clnk&gl=uk
#define NORMAL_PRIORITY_CLASS 32
#define IDLE_PRIORITY_CLASS 64
#define HIGH_PRIORITY_CLASS 128
#define REALTIME_PRIORITY_CLASS 256
#define ABOVE_NORMAL_PRIORITY_CLASS 32768
#define BELOW_NORMAL_PRIORITY_CLASS 16384

typedef struct _CHAR_INFO {
    union { TCHAR AsciiChar; WCHAR UnicodeChar; } Char;
    WORD Attributes;
} CHAR_INFO, *PCHAR_INFO;

typedef struct _CONSOLE_CURSOR_INFO {
    DWORD dwSize;
    BOOL bVisible;
} CONSOLE_CURSOR_INFO, *PCONSOLE_CURSOR_INFO;

typedef struct _KEY_EVENT_RECORD {
    BOOL bKeyDown;
    WORD wRepeatCount;
    WORD wVirtualKeyCode;
    WORD wVirtualScanCode;
    union { TCHAR AsciiChar; WCHAR UnicodeChar; } uChar;
    DWORD dwControlKeyState;
} KEY_EVENT_RECORD, *PKEY_EVENT_RECORD;

#define RIGHT_CTRL_PRESSED 0x0004
#define LEFT_CTRL_PRESSED  0x0008
#define RIGHT_ALT_PRESSED  0x0001
#define LEFT_ALT_PRESSED   0x0002
#define SHIFT_PRESSED      0x0010

#define VK_SPACE  0x20
#define VK_RETURN 0x0D
#define VK_BACK   0x08
#define VK_TAB    0x09
#define VK_ESCAPE 0x1B
#define VK_LEFT   0x25
#define VK_UP     0x26
#define VK_RIGHT  0x27
#define VK_DOWN   0x28
#define VK_DELETE 0x2E
#define VK_HOME   0x24
#define VK_END    0x23
#define VK_INSERT 0x2D

#ifndef _T
#define _T(x) x
#endif



// https://webcache.googleusercontent.com/search?q=cache:xaaywBK_sCkJ:https://sourceforge.net/u/cstrauss/w32api/ci/f3077014e6186628344d580460bfafe4d3b52c9d/tree/include/winbase.h%3Fformat%3Draw+&cd=1&hl=en&ct=clnk&gl=uk
#define STARTF_USESHOWWINDOW 1
#define STARTF_USESHOWWINDOW 1

// http://www.lugaru.com/man/Other.Process.Primitives.html
#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms679351(v=vs.85).aspx
#define FORMAT_MESSAGE_FROM_HMODULE 0x00000800
#define FORMAT_MESSAGE_FROM_SYSTEM 0x00001000
#define FORMAT_MESSAGE_ARGUMENT_ARRAY 0x00002000
#define FORMAT_MESSAGE_IGNORE_INSERTS 0x00000200
#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define MSG_FIRST_CMD_MSG_ID 0x10000

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms680621(v=vs.85).aspx
#define SEM_FAILCRITICALERRORS 0x0001

#if !defined(HINSTANCE_ERROR)
#define HINSTANCE_ERROR 32


#endif

#define IMAGE_SUBSYSTEM_WINDOWS_GUI 2
#define _cdecl
#define _stdcall
#define __cdecl
#define SCS_POSIX_BINARY 4

#define NTSTATUS DWORD
#define STATUS_SUCCESS                   ((DWORD)0x00000000L)
#define STATUS_UNSUCCESSFUL              ((DWORD)0xC0000001L)
#define STATUS_BUFFER_OVERFLOW           ((DWORD)0x80000005L)
#define STATUS_INVALID_PARAMETER         ((DWORD)0xC000000DL)

// FormatMessageWithArgs
// https://github.com/gasgas4/NT_4.0_SourceCode/blob/84a03f73738328ea66034dca7cda79a857623720/nt4/private/windows/shell/cabinet/message.c

// FormatMessage
// https://github.com/kerneltravel/longene_travel/blob/daa01b979536498ec2552db8e60abeef31894d72/wine-1.0-longene/dlls/kernel32/format_msg.c
// https://github.com/gasgas4/NT_4.0_SourceCode/blob/84a03f73738328ea66034dca7cda79a857623720/nt4/private/windows/base/client/message.c

#define UOI_NAME 2

#if defined(__GNUC__) || defined(__clang__)
#define FIELD_OFFSET(type, field) offsetof(type, field)
#else
#define FIELD_OFFSET(type, field) ((LONG)(INT_PTR)&(((type *)0)->field))


#endif

LPTCH WINAPI GetEnvironmentStrings(void);

DWORD WINAPI GetEnvironmentVariable(
  LPCTSTR lpName,
  LPTSTR  lpBuffer,
  DWORD   nSize
);

DWORD WINAPI GetModuleFileName(
  _In_opt_ HMODULE hModule,
  _Out_    LPTSTR  lpFilename,
  _In_     DWORD   nSize
);


BOOL WINAPI SetEnvironmentVariable(
  _In_     LPCTSTR lpName,
  _In_opt_ LPCTSTR lpValue
);

BOOL WINAPI CloseHandle(
  _In_ HANDLE hObject
);

/* CreateProcess: declaracao simplificada acima */

BOOL WINAPI GetExitCodeProcess(
  _In_  HANDLE  hProcess,
  _Out_ LPDWORD lpExitCode
);

DWORD WINAPI WaitForSingleObject(
  _In_ HANDLE hHandle,
  _In_ DWORD  dwMilliseconds
);

BOOL WINAPI DuplicateHandle(
  _In_  HANDLE   hSourceProcessHandle,
  _In_  HANDLE   hSourceHandle,
  _In_  HANDLE   hTargetProcessHandle,
  _Out_ LPHANDLE lpTargetHandle,
  _In_  DWORD    dwDesiredAccess,
  _In_  BOOL     bInheritHandle,
  _In_  DWORD    dwOptions
);

BOOL ShellExecuteEx(
  _Inout_ SHELLEXECUTEINFO *pExecInfo
);

BOOL WINAPI TerminateProcess(
  _In_ HANDLE hProcess,
  _In_ UINT   uExitCode
);

SIZE_T WINAPI VirtualQuery(
  _In_opt_ LPCVOID                   lpAddress,
  _Out_    LPVOID lpBuffer,
  _In_     SIZE_T                    dwLength
);

void WINAPI OutputDebugStringA(
  _In_opt_ LPCTSTR lpOutputString
);


char *str_append(char *a, char *b);


#ifndef ARGUMENT_PRESENT
#define ARGUMENT_PRESENT(Argument) (Argument != 0)
#endif // ARGUMENT_PRESENT

#include "_locale.h"
#include "_time.h"
#include "_memory.h"
#include "cmdmsg.h"
#include "_file.h"
#include "_msg.h"
#include "_error.h"
#include "_path.h"
#include "_find.h"

typedef intptr_t INT_PTR;
typedef uint16_t LANGID;
typedef uintptr_t UINT_PTR;
typedef WORD SORTID;
typedef struct { USHORT wLanguageID; USHORT wSortID; } LCID_DECIMAL;
#define MAKELANGID(p,s) ((LANGID)(((USHORT)(s)<<10)|(USHORT)(p)))
#define PRIMARYLANGID(lgid) ((USHORT)(lgid)&0x3ff)
#define SUBLANGID(lgid) ((USHORT)(lgid)>>10)
#define MAKELCID(us,srt) ((LCID)(((DWORD)(USHORT)(srt)<<16)|(DWORD)(USHORT)(us)))
#define SORT_DEFAULT 0
#define LANG_ENGLISH 0x09
#define SUBLANG_ENGLISH_US 0x01

typedef struct _OSVERSIONINFOA { DWORD dwOSVersionInfoSize; DWORD dwMajorVersion; DWORD dwMinorVersion; DWORD dwBuildNumber; DWORD dwPlatformId; CHAR szCSDVersion[128]; } OSVERSIONINFOA;
#define OSVERSIONINFO OSVERSIONINFOA

void WINAPI SetThreadLocale(LCID);
LCID WINAPI GetUserDefaultLCID(void);
LCID WINAPI GetSystemDefaultLCID(void);
int WINAPI CompareStringA(LCID, DWORD, LPCSTR, int, LPCSTR, int);
int WINAPI CompareStringW(LCID, DWORD, LPCWSTR, int, LPCWSTR, int);
#define CompareString CompareStringA
#define CSTR_EQUAL 2
#define CSTR_GREATER_THAN 3
#define CSTR_LESS_THAN 1

typedef void (WINAPI *FARPROC)(void);
HMODULE WINAPI GetModuleHandle(LPCTSTR);
FARPROC WINAPI GetProcAddress(HMODULE, LPCSTR);
#define GetModuleHandleA GetModuleHandle
#define GetModuleHandleW GetModuleHandle

#define ERROR_INSUFFICIENT_BUFFER 122
#define ERROR_NO_MORE_FILES 18
#define ERROR_INVALID_HANDLE 6
#define ERROR_INVALID_PARAMETER 87
#define ERROR_FILE_NOT_FOUND 2
#define ERROR_PATH_NOT_FOUND 3
#define ERROR_ACCESS_DENIED 5
#define ERROR_NOT_ENOUGH_MEMORY 8
#define ERROR_INVALID_DRIVE 15
#define ERROR_NOT_DOS_DISK 26
#define ERROR_BAD_DEVICE 12
#define ERROR_NO_PROC_SLOTS 89
#define ERROR_SHARING_VIOLATION 32
#define ERROR_LOCK_VIOLATION 33
#define ERROR_DIRECTORY 267
#define ERROR_ALREADY_EXISTS 183
#define ERROR_DISK_FULL 112
#define ERROR_INTERNAL_ERROR 1359
#define ERROR_SUCCESS 0
#define NO_ERROR 0
#define ERROR_BAD_COMMAND 22

/* XP shim additions */
typedef struct _NTTIB { PVOID StackBase; PVOID StackLimit; PVOID SubSystemTib; PVOID FiberData; PVOID ArbitraryUserPointer; PVOID Self; } NTTIB, *PNTTIB;
typedef struct _TEB { NTTIB NtTib; } TEB, *PTEB;
static inline PTEB NtCurrentTeb(void) {
    static TEB teb;
    teb.NtTib.StackBase = (PVOID)0x7ffffffff000ULL;
    teb.NtTib.StackLimit = (PVOID)0x10000;
    return &teb;
}
UINT WINAPI GetConsoleOutputCP(void);
typedef struct _CPINFO { UINT MaxCharSize; BYTE DefaultChar[2]; BYTE LeadByte[12]; } CPINFO, *LPCPINFO;
BOOL WINAPI GetCPInfo(UINT, LPCPINFO);
static inline int _get_osfhandle(int fd) { return fd; }
#define _tcsspn strspn
#define _tell(f) ((long)lseek((int)(long)(f), 0, SEEK_CUR))

/* Safer API / policies - stub: sem restricao (comportamento Linux nativo) */
typedef struct _SAFER_CODE_PROPERTIES { DWORD cbSize; DWORD dwCheckFlags; HANDLE hImage; LPCWSTR ImagePath; DWORD dwWx; DWORD dwNx; PVOID lpReserved; } SAFER_CODE_PROPERTIES, *PSAFER_CODE_PROPERTIES;
typedef HANDLE SAFER_LEVEL_HANDLE;
#define SAFER_CRITERIA_IMAGEPATH 0x00002
#define SAFER_TOKEN_NULL_IF_EQUAL 0x8
#define ERROR_ACCESS_DISABLED_BY_POLICY 1260L
#define ERROR_PROC_NOT_FOUND 127L
#define ERROR_SEVERITY_ERROR 0x40000000L
#define EXCEPTION_EXECUTE_HANDLER 1
#define SHIFT_PRESSED  0x0001
#define FILE_TYPE_UNKNOWN 0x0000
#define FILE_TYPE_DISK     0x0001
#define FILE_TYPE_CHAR     0x0002
#define FILE_TYPE_PIPE     0x0003
static inline DWORD GetFileType(HANDLE h) {
    int fd = -1;
    if (h != NULL) {
        if (h == (HANDLE)STDIN_FILENO || h == (HANDLE)STDOUT_FILENO || h == (HANDLE)STDERR_FILENO) {
            fd = (int)(long)h;
        } else if ((long)h > 2) {
            FILE *f = (FILE *)h;
            fd = fileno(f);
        }
    }
    if (fd >= 0) {
        if (isatty(fd)) return FILE_TYPE_CHAR;
        struct stat st;
        if (fstat(fd, &st) == 0 && (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode))) return FILE_TYPE_PIPE;
    }
    return FILE_TYPE_DISK;
}
static inline void MessageBeep(UINT u) { (void)u; }
static inline BOOLEAN IsDBCSCodePage(void) { return FALSE; }
#define TIME_NOSECONDS 0x00000004
static inline void WinFmtToStrftime(const char *in, char *out, int cch) {
    while (*in && cch > 4) {
        if (in[0]=='d'&&in[1]=='d') { *out++='%'; *out++='d'; in+=2; }
        else if (*in=='d') { *out++='%'; *out++='e'; in++; }
        else if (in[0]=='M'&&in[1]=='M') { *out++='%'; *out++='m'; in+=2; }
        else if (*in=='M') { *out++='%'; *out++='m'; in++; }
        else if (in[0]=='y'&&in[1]=='y'&&in[2]=='y'&&in[3]=='y') { *out++='%'; *out++='Y'; in+=4; }
        else if (in[0]=='y'&&in[1]=='y') { *out++='%'; *out++='y'; in+=2; }
        else if (in[0]=='H'&&in[1]=='H') { *out++='%'; *out++='H'; in+=2; }
        else if (in[0]=='h'&&in[1]=='h') { *out++='%'; *out++='I'; in+=2; }
        else if (in[0]=='m'&&in[1]=='m') { *out++='%'; *out++='M'; in+=2; }
        else if (in[0]=='s'&&in[1]=='s') { *out++='%'; *out++='S'; in+=2; }
        else if (in[0]=='t'&&in[1]=='t') { *out++='%'; *out++='p'; in+=2; }
        else if (*in=='H') { *out++='%'; *out++='H'; in++; }
        else if (*in=='h') { *out++='%'; *out++='I'; in++; }
        else if (*in=='m') { *out++='%'; *out++='M'; in++; }
        else if (*in=='s') { *out++='%'; *out++='S'; in++; }
        else if (*in=='t') { *out++='%'; *out++='p'; in++; }
        else if (*in=='\'') { in++; while(*in && *in!='\'') { *out++=*in++; } if(*in=='\'') in++; }
        else { *out++=*in++; }
    }
    *out=0;
}
static inline struct tm *SysTimeToTm(LPVOID lpSys, struct tm *tm_out) {
    if (lpSys != NULL) {
        LPSYSTEMTIME st = (LPSYSTEMTIME)lpSys;
        memset(tm_out, 0, sizeof(*tm_out));
        tm_out->tm_year = st->wYear - 1900;
        tm_out->tm_mon  = st->wMonth - 1;
        tm_out->tm_mday = st->wDay;
        tm_out->tm_hour = st->wHour;
        tm_out->tm_min  = st->wMinute;
        tm_out->tm_sec  = st->wSecond;
        tm_out->tm_wday = st->wDayOfWeek;
        return tm_out;
    }
    time_t now = time(NULL);
    return localtime_r(&now, tm_out);
}
static inline int GetTimeFormat(LCID lcid, DWORD dwFlags, LPVOID lpSys, LPCTSTR fmt, LPTSTR buf, int cch) {
    struct tm tm_out;
    struct tm *lt = SysTimeToTm(lpSys, &tm_out);
    char fmt_buf[128];
    if (fmt != NULL && fmt[0]) {
        WinFmtToStrftime(fmt, fmt_buf, sizeof(fmt_buf));
    } else {
        strcpy(fmt_buf, "%H:%M");
    }
    if ((dwFlags & TIME_NOSECONDS) != 0) {
        char *s = strstr(fmt_buf, ":%S");
        if (s) memmove(s, s+3, strlen(s+3)+1);
    }
    (void)lcid;
    if (cch < 32) return 0;
    strftime(buf, cch, fmt_buf, lt);
    return (int)strlen(buf);
}
static inline int GetDateFormat(LCID lcid, DWORD dwFlags, LPVOID lpSys, LPCTSTR fmt, LPTSTR buf, int cch) {
    struct tm tm_out;
    struct tm *lt = SysTimeToTm(lpSys, &tm_out);
    char fmt_buf[128];
    if (fmt != NULL && fmt[0]) {
        WinFmtToStrftime(fmt, fmt_buf, sizeof(fmt_buf));
    } else {
        strcpy(fmt_buf, "%d/%m/%Y");
    }
    (void)dwFlags; (void)lcid;
    if (cch < 32) return 0;
    strftime(buf, cch, fmt_buf, lt);
    return (int)strlen(buf);
}
#define NOTHING ((void)0)
#define _tpopen popen
#define _pclose pclose
static inline BOOL SaferIdentifyLevel(DWORD dwNumProperties, PSAFER_CODE_PROPERTIES pProperties, SAFER_LEVEL_HANDLE *pLevelHandle, LPVOID lpReserved) { (void)dwNumProperties;(void)pProperties;(void)lpReserved; *pLevelHandle = (SAFER_LEVEL_HANDLE)0x1; return TRUE; }
static inline BOOL SaferComputeTokenFromLevel(SAFER_LEVEL_HANDLE LevelHandle, HANDLE hAccessToken, HANDLE *phRestrictedToken, DWORD dwFlags, LPVOID lpReserved) { (void)LevelHandle;(void)hAccessToken;(void)dwFlags;(void)lpReserved; *phRestrictedToken = NULL; return TRUE; }
static inline BOOL SaferCloseLevel(SAFER_LEVEL_HANDLE hLevelHandle) { (void)hLevelHandle; return TRUE; }
static inline BOOL SaferRecordEventLogEntry(SAFER_LEVEL_HANDLE hLevelHandle, LPCWSTR szTargetPath, LPVOID lpReserved) { (void)hLevelHandle;(void)szTargetPath;(void)lpReserved; return TRUE; }
static inline BOOL ImpersonateLoggedOnUser(HANDLE hToken) { (void)hToken; return TRUE; }


#define lstrcmp strcmp
#define lstrcmpi strcasecmp
static inline BOOL RevertToSelf(void) { return TRUE; }


/* Console types (XP era) */
typedef struct _COORD { SHORT X; SHORT Y; } COORD, *PCOORD;
typedef struct _SMALL_RECT { SHORT Left; SHORT Top; SHORT Right; SHORT Bottom; } SMALL_RECT, *PSMALL_RECT;
typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
    COORD dwSize;
    COORD dwCursorPosition;
    WORD wAttributes;
    SMALL_RECT srWindow;
    COORD dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO, *PCONSOLE_SCREEN_BUFFER_INFO;
typedef struct _CONSOLE_READCONSOLE_CONTROL {
    ULONG nLength;
    ULONG nInitialChars;
    ULONG dwCtrlWakeupMask;
    ULONG dwControlKeyState;
} CONSOLE_READCONSOLE_CONTROL, *PCONSOLE_READCONSOLE_CONTROL;
BOOL WINAPI GetConsoleScreenBufferInfo(FILE*, PCONSOLE_SCREEN_BUFFER_INFO);
BOOL WINAPI WriteConsole(FILE*, LPCVOID, DWORD, LPDWORD, LPVOID);
BOOL WINAPI ReadConsole(FILE*, LPVOID, DWORD, LPDWORD, PCONSOLE_READCONSOLE_CONTROL);
BOOL WINAPI FlushConsoleInputBuffer(FILE*);
BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE, BOOL);
BOOL WINAPI SetConsoleMode(FILE*, DWORD);
BOOL WINAPI SetConsoleTextAttribute(FILE*, WORD);
BOOL WINAPI SetConsoleCursorPosition(FILE*, COORD);
BOOL WINAPI SetConsoleCursorInfo(FILE*, LPVOID);
BOOL WINAPI FillConsoleOutputCharacterA(FILE*, TCHAR, DWORD, COORD, LPDWORD);
#define FillConsoleOutputCharacter FillConsoleOutputCharacterA
BOOL WINAPI FillConsoleOutputAttribute(FILE*, WORD, DWORD, COORD, LPDWORD);
BOOL WINAPI ReadConsoleOutputCharacterA(FILE*, LPTSTR, DWORD, COORD, LPDWORD);
#define ReadConsoleOutputCharacter ReadConsoleOutputCharacterA
BOOL WINAPI WriteConsoleOutputCharacterA(FILE*, LPCTSTR, DWORD, COORD, LPDWORD);
#define WriteConsoleOutputCharacter WriteConsoleOutputCharacterA
BOOL WINAPI ReadConsoleInputA(FILE*, LPVOID, DWORD, LPDWORD);
#define ReadConsoleInput ReadConsoleInputA
BOOL WINAPI SetConsoleCP(UINT);
BOOL WINAPI SetConsoleOutputCP(UINT);
BOOL WINAPI SetConsoleInputExeNameW(LPCWSTR);
/* ReadConsole extras faltantes */
typedef struct _MOUSE_EVENT_RECORD { COORD dwMousePosition; DWORD dwButtonState; DWORD dwControlKeyState; DWORD dwEventFlags; } MOUSE_EVENT_RECORD;
typedef struct _INPUT_RECORD { WORD EventType; union { KEY_EVENT_RECORD KeyEvent; MOUSE_EVENT_RECORD MouseEvent; } Event; } INPUT_RECORD, *PINPUT_RECORD;
#define VK_F8 0x77
#define MB_ICONEXCLAMATION 0x00000030
#define KEY_EVENT 0x0001
#define MOUSE_EVENT 0x0002
#define WINDOW_BUFFER_SIZE_EVENT 0x0004
BOOL WINAPI ScrollConsoleScreenBuffer(FILE*, SMALL_RECT*, SMALL_RECT*, COORD, CHAR_INFO*);





#endif


typedef BOOL (WINAPI *PHANDLER_ROUTINE)(DWORD);




#define IMAGE_SUBSYSTEM_UNKNOWN 0
#define PEB PVOID
#define PIMAGE_NT_HEADERS PVOID
