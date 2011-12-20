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

#ifndef XO_H
#define XO_H

#include <stdbool.h>

#include "canvas.h"

#define xo_draw_background_intro(c) xo_draw_background_box(c, NULL)

void xo_intro(Canvas c);

// Layout and layout elements
void xo_draw_background_box(Canvas c, Canvas o);
void xo_draw_game_layout(Canvas c, Canvas o);
void xo_draw_the_chosen_one(Canvas c, Canvas o, bool creature_x);
void xo_draw_life(Canvas c, int n);
void xo_draw_timebar(Canvas c, int lenght, int *options);
void xo_draw_timebar100(Canvas c, int percent, int *options);

void xo_draw_creature(Canvas c, Canvas o, int x, int y, bool creature_x,
                      int *options);
int xo_draw_creature_random_point(Canvas c, Canvas o, bool creature_x,
                                  int *options);
int xo_draw_bunch_creatures(Canvas c, Canvas o, bool creature_x, int n);
void xo_draw_random_creatures(Canvas c, Canvas o, int n, int *in_xo);

#endif
