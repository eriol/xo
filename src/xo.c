#include <stdbool.h>
#include <unistd.h>

#include "xo.h"

#define INTRO_SPEED 100000 /* microseconds */
#define LAYOUT_BOTTOM_DELTA 7
#define CREATURE_SIZE_X 5
#define CREATURE_SIZE_Y 5

canvas_element_t obstacle_mark = L'☠';

void xo_background_box(Canvas c, Canvas o)
{
    canvas_border(c, L"♠♣☮");
    if (o != NULL) {
        canvas_border(o, L"☠☠☠");
    }
}

void xo_intro(Canvas c)
{
    int cols = canvas_get_cols(c);
    int rows = canvas_get_rows(c);
    int center = (int) (rows / 2);
    int multi_creature_lenght = 8;

    for (int i = 0; i < cols + multi_creature_lenght; i++) {
        canvas_clean(c);
        // Forward
        xo_creature(c, NULL,
                    center - CREATURE_SIZE_Y - 2,
                    0 - multi_creature_lenght + i,
                    true);
        xo_creature(c, NULL,
                    center - CREATURE_SIZE_X - 2,
                    CREATURE_SIZE_X - multi_creature_lenght + i,
                    false);
        //Backward
        xo_creature(c, NULL, center + 2, cols - 2 - i, false);
        xo_creature(c, NULL, center + 2, cols - 2 + CREATURE_SIZE_X - i, true);
        xo_background_intro(c);
        canvas_draw(c);
        usleep(INTRO_SPEED);
    }
}

void xo_game_layout(Canvas c, Canvas o)
{
    int x = canvas_get_rows(c) - LAYOUT_BOTTOM_DELTA;
    int y = canvas_get_cols(c) - 1;

    xo_background_box(c, o);
    canvas_horizontal_line(c, x, 1, y, L'⣿');
    if (o != NULL) {
        canvas_box_fill(o, x, 1, canvas_get_rows(c) - 1, y , obstacle_mark);
    }
}

void xo_creature(Canvas c, Canvas o, int x, int y, bool creature_x)
{
    canvas_element_t x_creature[CREATURE_SIZE_X][CREATURE_SIZE_Y] = {
        L"✖   ✖",
        L" ⥀ ⥁ ",
        L"  ✖  ",
        L" ✖ ✖ ",
        L"✖   ✖"
    };

    canvas_element_t o_creature[CREATURE_SIZE_X][CREATURE_SIZE_Y] = {
        L"  ●  ",
        L" ◐ ◑ ",
        L"●   ●",
        L" ●⟰● ",
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
        }
    }
}
