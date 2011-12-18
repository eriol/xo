#ifndef XO_H
#define XO_H

#include <stdbool.h>

#include "canvas.h"

#define xo_draw_background_intro(c) xo_draw_background_box(c, NULL)

void xo_intro(Canvas c);

void xo_draw_background_box(Canvas c, Canvas o);
void xo_draw_game_layout(Canvas c, Canvas o);

void xo_insert_creature(Canvas c, Canvas o, int x, int y, bool creature_x);
int xo_insert_creature_random_point(Canvas c, Canvas o, bool creature_x);
int xo_insert_bunch_creatures(Canvas c, Canvas o, bool creature_x, int n);
void xo_insert_random_creatures(Canvas c, Canvas o, int n, int *in_xo);

#endif
