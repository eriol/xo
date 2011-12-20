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
