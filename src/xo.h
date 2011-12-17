#ifndef XO_H
#define XO_H

#include <stdbool.h>

#include "canvas.h"

#define xo_background_intro(c) xo_background_box(c, NULL)

void xo_creature(Canvas c, int x, int y, bool creature_x);
void xo_background_box(Canvas c, Canvas o);
void xo_game_layout(Canvas c, Canvas o);
void xo_intro(Canvas c);

#endif
