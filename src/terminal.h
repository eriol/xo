#ifndef TERMINAL_H
#define TERMINAL_H

char getch(void);
void terminal_clear(void);
void terminal_draw_horizontal_line(int x, int y, int lenght, char ch);
void terminal_draw_vertical_line(int x, int y, int lenght, char ch);
int terminal_get_size(unsigned short *row, unsigned short *col);
void terminal_put_chat_at(int x, int y, char ch);

#endif /* TERMINAL_H */
