#ifndef _PROCESS_H_
#define _PROCESS_H_
#include <unistd.h>
#include <sys/wait.h>
#define _getpid getpid
#define _execl execl
#define _execv execv
#define _spawnl(f,a0,a1,ap...) fork_or_error()
#define _cwait(stat,pid,act) waitpid(pid,stat,0)
#endif
