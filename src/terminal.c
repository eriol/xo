#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


char getch(void) {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcgetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}

/* terminal_get_size -- get the terminal window size and store it in row and
 * col pointers.
 * 
 * Return 0 in case of success, -1 otherwise
 */

int terminal_get_size(unsigned short *row, unsigned short *col)
{
    struct winsize ws;

    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1) {
        perror("get_terminal_size: can't get terminal size");
        return -1;
    }

    *row = ws.ws_row;
    *col = ws.ws_col;

    return 0;
}
