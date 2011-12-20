#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

int terminal_set_cbreak(int fd, struct termios *prev_termios);
int terminal_restore(int fd, struct termios *t);
char terminal_read_1_byte(int fd);
void terminal_clear(void);
void terminal_draw_horizontal_line(int x, int y, int lenght, wchar_t ch);
void terminal_draw_vertical_line(int x, int y, int lenght, wchar_t ch);
int terminal_get_size(unsigned short *row, unsigned short *col);
void terminal_put_chat_at(int x, int y, wchar_t ch);

#endif
