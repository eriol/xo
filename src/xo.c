#include <unistd.h>

#include "xo.h"

#define INTRO_SPEED 100000 /* microseconds */

void xo_layout(Canvas c)
{
    canvas_element_t d[] = L"♠♣☮";
    int sep = canvas_get_rows(c) - 7;
    canvas_box(c, 0, 0, canvas_get_rows(c) - 1, canvas_get_cols(c) - 1, d);
    canvas_horizontal_line(c, sep, 1, canvas_get_cols(c) - 1, L'⣿');
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

void xo_intro_screen(Canvas c)
{
    for (int i = 0; i < canvas_get_cols(c); i++) {
        canvas_clean(c);
        xo_layout(c);
        xo_x_creature(c, 2, 2 + i);
        xo_o_creature(c, 2, 7 + i);
        canvas_draw(c);
        usleep(INTRO_SPEED);
    }
}
