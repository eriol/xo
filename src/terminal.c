/*
 * Copyright 2011 Daniele Tricoli <eriol@mornie.org>
 *
 * This file is part of xo.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see http://www.gnu.org/licenses/.
 */

#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <wchar.h>

int terminal_set_cbreak(int fd, struct termios *prev_termios)
{
    struct termios t;
    if (tcgetattr(fd, &t) == -1) {
        perror("terminal_set_cbreak: failed to fetch terminal attributes");
        return -1;
    }

    if (prev_termios != NULL)
        *prev_termios = t;

    t.c_lflag &= ~(ICANON | ECHO);

    t.c_cc[VMIN] = 1;    // One character at time
    t.c_cc[VTIME] = 0;   // Blocking

    if (tcsetattr(fd, TCSANOW, &t) == -1) {
        perror("terminal_set_cbreak: failed to set terminal attributes");
        return -1;
    }

    return 0;
}

int terminal_restore(int fd, struct termios *t)
{
    if (tcsetattr(fd, TCSANOW, t) == -1) {
        perror("terminal_set_cbreak: failed to set terminal attributes");
        return -1;
    }

    return 0;
}

char terminal_read_1_byte(int fd)
{
    char buf;
    if (read(fd, &buf, 1) < 0)
        perror ("terminal_read_1_byte: failed to read");

    return buf;
}

/**
 * terminal_get_size -- get the terminal window size and store it in row and
 * col pointers.
 * 
 * @return 0 in case of success, -1 otherwise
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

/**
 * terminal_clear -- clear the terminal window and reset the cursor to the
 * top-left.
 */

void terminal_clear(void)
{
    fwprintf(stdout, L"\033[2J\033[1;1H");
}

void terminal_put_chat_at(int x, int y, wchar_t ch)
{
    fwprintf(stdout, L"\033[%d;%dH%c", x, y, ch);
    fflush(stdout);
}

void terminal_draw_horizontal_line(int x, int y, int lenght, wchar_t ch)
{
    for(int i = y; i <= lenght; i++) {
        terminal_put_chat_at(x, i, ch);
    }
}

void terminal_draw_vertical_line(int x, int y, int lenght, wchar_t ch)
{
    for(int i = x; i <= lenght; i++) {
        terminal_put_chat_at(i, y, ch);
    }
}
