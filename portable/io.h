#ifndef _IO_H_
#define _IO_H_
#include <unistd.h>
#include <fcntl.h>
#define _isatty isatty
#define _lseek lseek
#define _open open
#define _close close
#define _read read
#define _write write
#define _setmode(fd,m) (0)
#define _O_RDONLY O_RDONLY
#define _O_WRONLY O_WRONLY
#define _O_RDWR   O_RDWR
#define _O_APPEND O_APPEND
#define _O_CREAT  O_CREAT
#define _O_TRUNC  O_TRUNC
#define _O_BINARY 0
#define _O_TEXT   0
#define _S_IREAD  S_IRUSR
#define _S_IWRITE S_IWUSR
#endif
