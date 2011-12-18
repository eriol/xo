#ifndef XO_H
#define XO_H

#include <stdbool.h>

#include "canvas.h"

#define xo_draw_background_intro(c) xo_draw_background_box(c, NULL)

void xo_draw_background_box(Canvas c, Canvas o);
void xo_draw_game_layout(Canvas c, Canvas o);
void xo_insert_creature(Canvas c, Canvas o, int x, int y, bool creature_x);
int xo_insert_creature_random(Canvas c, Canvas o, bool creature_x);
void xo_intro(Canvas c);

#endif
