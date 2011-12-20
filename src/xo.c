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

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "xo.h"
#include "utils.h"

#define INTRO_SPEED 100000 /* microseconds */
#define LAYOUT_BOTTOM_DELTA 7
#define CREATURE_SIZE_X 5
#define CREATURE_SIZE_Y 5
#define LIFE_SIZE_X 5
#define LIFE_SIZE_Y 5
#define LIFE_STARTING_POSITION_Y 7
#define MAX_TRIES 5

canvas_element_t obstacle_mark = L'☠';

void xo_intro(Canvas c)
{
    int cols = canvas_get_cols(c);
    int rows = canvas_get_rows(c);
    int center = (int) (rows / 2);
    int multi_creature_lenght = 8;
    int color1, color2, color3, color4;

    color1 = random_fcolor();
    color2 = random_fcolor();
    color3 = random_fcolor();
    color4 = random_fcolor();

    for (int i = 0; i < cols + multi_creature_lenght; i++) {
        canvas_clean(c);
        // Forward
        xo_draw_creature(c, NULL, center - CREATURE_SIZE_Y - 2,
                         0 - multi_creature_lenght + i, true,
                         (int []) {NONE, color1, NONE});
        xo_draw_creature(c, NULL, center - CREATURE_SIZE_X - 2,
                         CREATURE_SIZE_X - multi_creature_lenght + i,
                         false, (int []) {NONE, color2, NONE});
        //Backward
        xo_draw_creature(c, NULL, center + 2, cols -2 - i, false,
                         (int []) {NONE, color3, NONE});
        xo_draw_creature(c, NULL, center + 2, cols -2 + CREATURE_SIZE_X - i,
                         true, (int []) {NONE, color4, NONE});
        xo_draw_background_intro(c);
        canvas_draw(c);
        usleep(INTRO_SPEED);
    }
}

void xo_draw_background_box(Canvas c, Canvas o)
{
    canvas_border(c, L"♠♣☮", (int []) {NONE, F_GREEN, NONE},
                             (int []) {NONE, F_YELLOW, NONE},
                             (int []) {NONE, F_MAGENTA, NONE});
    if (o != NULL) {
        canvas_border(o, L"☠☠☠", NULL, NULL, NULL);
    }
}

void xo_draw_game_layout(Canvas c, Canvas o)
{
    int x = canvas_get_rows(c) - LAYOUT_BOTTOM_DELTA;
    int y = canvas_get_cols(c) - 1;

    xo_draw_background_box(c, o);
    canvas_horizontal_line(c, x, 1, y - 1, L'⣿', (int []) {NONE, F_CYAN, NONE});
    canvas_vertical_line(c, x + 1, 6, 5, L'⣿', (int []) {NONE, F_CYAN, NONE});
    canvas_vertical_line(c, x + 1, 24, 5, L'⣿', (int []) {NONE, F_CYAN, NONE});

    if (o != NULL) {
        canvas_box_fill(o, x, 1, canvas_get_rows(c) - 1, y, obstacle_mark,
                        NULL);
    }
}

void xo_draw_creature(Canvas c, Canvas o, int x, int y, bool creature_x,
                      int *options)
{
    canvas_element_t x_creature[CREATURE_SIZE_X][CREATURE_SIZE_Y] = {
        L"✖   ✖",
        L" ◔ ◔ ",
        L"  ✖  ",
        L" ✖ ✖ ",
        L"✖   ✖"
    };

    canvas_element_t o_creature[CREATURE_SIZE_X][CREATURE_SIZE_Y] = {
        L"  ●  ",
        L" ◐ ◑ ",
        L"●   ●",
        L" ●⏟● ",
        L"  ●  "
    };

    canvas_element_t e;

    for (int i = 0; i < CREATURE_SIZE_X; i++) {
        for (int j = 0; j < CREATURE_SIZE_Y; j++) {
            if (creature_x) {
                e = x_creature[i][j];
            } else {
                e = o_creature[i][j];
            }
            canvas_set_element(c, i + x, j + y, e);
            if (o != NULL) {
                canvas_set_element(o, i + x, j + y, obstacle_mark);
            }
            if (canvas_has_advanced_options(c) && options != NULL) {
                canvas_set_element_options(c, i + x, j + y, options);
            }
        }
    }
}

void xo_draw_life(Canvas c, int n)
{
    canvas_element_t life[LIFE_SIZE_X][LIFE_SIZE_Y] = {
        L" ♥.♥ ",
        L"♥♥♥♥♥",
        L"♥♥♥♥♥",
        L" ♥♥♥ ",
        L"  ♥  "
    };

    int x = canvas_get_rows(c) - LAYOUT_BOTTOM_DELTA + 1;
    int life_position_y[3] = {LIFE_STARTING_POSITION_Y,
                              LIFE_STARTING_POSITION_Y + LIFE_SIZE_Y + 1,
                              LIFE_STARTING_POSITION_Y + (LIFE_SIZE_Y * 2) + 2};

    // Player has only 3 lifes
    if (n > 3)
        n = 3;

    for (int y = 0; y < n; y++){
        for (int i = 0; i < LIFE_SIZE_X; i++) {
            for (int j = 0; j < LIFE_SIZE_Y; j++) {
                canvas_set_element(c, i + x, j + life_position_y[y],
                                   life[i][j]);
                if (canvas_has_advanced_options(c)) {
                    canvas_set_element_options(c, i + x, j + life_position_y[y],
                                               (int []) {BOLD, F_RED, NONE});
                }
            }
        }
    }
}

void xo_draw_timebar(Canvas c, int lenght, int *options)
{
    canvas_element_t timebar_mark = L'♦';
    int x1 = canvas_get_rows(c) - LAYOUT_BOTTOM_DELTA + 1;
    int y1 = 25;
    int x2 = canvas_get_rows(c) - 1;
    int y2 = y1 + lenght;
    int max_length = canvas_get_cols(c) - 1;

    if (y2 > max_length)
        y2 = max_length;

    // Clean before draw
    canvas_box_fill(c, x1, y1, x2, max_length, L' ', NULL);
    canvas_box_fill(c, x1, y1, x2, y2, timebar_mark, options);
}

void xo_draw_timebar100(Canvas c, int percent, int *options)
{
    int lenght;
    int max_length = (canvas_get_cols(c) - 1) - 25;

    lenght = (int) ((max_length * percent) / 100);

    xo_draw_timebar(c, lenght, options);
}

void xo_draw_the_chosen_one(Canvas c, Canvas o, bool creature_x)
{
    int x = canvas_get_rows(c) - LAYOUT_BOTTOM_DELTA + 1;
    xo_draw_creature(c, o, x, 1, creature_x, NULL);
}

static int check_collision(Canvas o, int x, int y)
{
    for (int i = 0; i < CREATURE_SIZE_X; i++) {
        for (int j = 0; j < CREATURE_SIZE_Y; j++) {
            if (canvas_get_element(o, x + i, y + j) == obstacle_mark) {
                return 1;
            }
        }
    }

    return 0;
}

int xo_draw_creature_random_point(Canvas c, Canvas o, bool creature_x,
                                  int *options)
{
    int x, y, x_min, y_min, x_max, y_max;

    x_min = 1;
    x_max = canvas_get_rows(c) - LAYOUT_BOTTOM_DELTA - CREATURE_SIZE_Y;
    y_min = 1;
    y_max = canvas_get_cols(c) - 1 - CREATURE_SIZE_X;

    x = randrange(x_min, x_max);
    y = randrange(y_min, y_max);

    if (!check_collision(o, x, y)) {
        xo_draw_creature(c, o, x, y, creature_x, options);
        return 1;
    }

    return 0;
}

int xo_draw_bunch_creatures(Canvas c, Canvas o, bool creature_x, int n)
{
    int inserted, res, current_try;

    inserted = res = current_try = 0;

    for (int i = 0; i < n; i++) {
        while(current_try < MAX_TRIES) {
            res = xo_draw_creature_random_point(c, o, creature_x,
                                                (int []) {NONE,
                                                          random_fcolor(),
                                                          NONE});
            if (res) {
                inserted++;
                break;
            } else {
                current_try++;
            }
        }
    }

    return inserted;
}

void xo_draw_random_creatures(Canvas c, Canvas o, int n, int *in_xo)
{
    bool creature;
    int res, current_try;
    res = current_try = 0;

    for (int i = 0; i < n; i++) {

        creature = (bool) randrange(0, 1);

        while(current_try < MAX_TRIES) {
            res = xo_draw_creature_random_point(c, o, creature,
                                                (int []) {NONE,
                                                          random_fcolor(),
                                                          NONE});
            if (res) {
                in_xo[creature]++;
                break;
            } else {
                current_try++;
            }
        }
    }
}

