#include <unistd.h>

#include "xo.h"

#define INTRO_SPEED 100000 /* microseconds */

canvas_element_t obstacle_mark = L'☠';

void xo_background_box(Canvas c, Canvas o)
{
    canvas_border(c, L"♠♣☮");
    if (o != NULL) {
        canvas_border(o, L"☠☠☠");
    }
}

void xo_game_layout(Canvas c, Canvas o)
{
    int x = canvas_get_rows(c) - 7;
    int y = canvas_get_cols(c) - 1;

    xo_background_box(c, o);
    canvas_horizontal_line(c, x, 1, y, L'⣿');
    if (o != NULL) {
        canvas_box_fill(o, x, 1, canvas_get_rows(c) - 1, y , obstacle_mark);
    }
}

void xo_x_creature(Canvas c, int x, int y)
{
    canvas_element_t x_creature[5][5] = {L"✖   ✖",
                                         L" ⥀ ⥁ ",
                                         L"  ✖  ",
                                         L" ✖ ✖ ",
                                         L"✖   ✖"};
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            canvas_set_element(c, i + x, j + y, x_creature[i][j]);
    }
}

void xo_o_creature(Canvas c, int x, int y)
{
    canvas_element_t x_creature[5][5] = {L"  ●  ",
                                         L" ◐ ◑ ",
                                         L"●   ●",
                                         L" ●⟰● ",
                                         L"  ●  "};
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            canvas_set_element(c, i + x, j + y, x_creature[i][j]);
    }
}

void xo_intro(Canvas c)
{
    int cols = canvas_get_cols(c);
    int rows = canvas_get_rows(c);
    int center = (int) (rows / 2);
    int creature_lenght = 5;
    int creature_height = 5;
    int multi_creature_lenght = 8;

    for (int i = 0; i < cols + multi_creature_lenght; i++) {
        canvas_clean(c);
        // Forward
        xo_x_creature(c,
                      center - creature_height - 2,
                      0 - multi_creature_lenght + i);
        xo_o_creature(c,
                      center - creature_height - 2,
                      creature_lenght - multi_creature_lenght + i);
        //Backward
        xo_o_creature(c, center + 2, cols - 2 - i);
        xo_x_creature(c, center + 2, cols - 2 + creature_lenght - i );
        xo_background_intro(c);
        canvas_draw(c);
        usleep(INTRO_SPEED);
    }
}
