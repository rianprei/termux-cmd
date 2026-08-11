#ifndef _CONIO_H_
#define _CONIO_H_
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
static inline int _getch(void) {
    struct termios oldt, newt;
    int c;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}
#endif
