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

#ifndef CANVAS_H
#define CANVAS_H

#include <wchar.h>

typedef wchar_t canvas_element_t;
typedef struct canvas_type *Canvas;
enum canvas_attributes {
    NONE,
    BOLD,
    UNDERSCORE,
    BLINK = 5,
    REVERSE = 7,
    CONCEALED
};
enum foreground_colors {
    F_BLACK = 30,
    F_RED,
    F_GREEN,
    F_YELLOW,
    F_BLUE,
    F_MAGENTA,
    F_CYAN,
    F_WHITE
};
enum backgroung_colors {
    B_BLACK = 40,
    B_RED,
    B_GREEN,
    B_YELLOW,
    B_BLUE,
    B_MAGENTA,
    B_CYAN,
    B_WHITE
};

Canvas canvas_create(int rows, int cols, bool advanced_options);
void canvas_clean(Canvas c);
void canvas_destroy(Canvas c);
int canvas_get_rows(Canvas c);
int canvas_get_cols(Canvas c);
bool canvas_has_advanced_options(Canvas c);
canvas_element_t canvas_get_element(Canvas c, int x, int y);
void canvas_set_element(Canvas c, int x, int y, canvas_element_t e);
void canvas_set_element_options(Canvas c, int x, int y, int *options);
void canvas_get_element_options(Canvas c, int x, int y, int *options);
void canvas_horizontal_line(Canvas c, int x, int y, int lenght,
                            canvas_element_t e, int* options);
void canvas_vertical_line(Canvas c, int x, int y, int lenght,
                          canvas_element_t e, int* options);
void canvas_box(Canvas c, int x1, int y1, int x2, int y2, canvas_element_t *d,
                int *horizontal_options, int *vertical_options,
                int *corners_options);
void canvas_border(Canvas c, canvas_element_t *d, int *horizontal_options,
                   int *vertical_options, int *corners_options);
void canvas_box_fill(Canvas c, int x1, int y1, int x2, int y2,
                     canvas_element_t d, int *options);
void canvas_draw(Canvas c);

int random_fcolor(void);
int random_bcolor(void);

#endif
