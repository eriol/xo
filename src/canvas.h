#ifndef CANVAS_H
#define CANVAS_H

#include <wchar.h>

typedef wchar_t canvas_element_t;
typedef struct canvas_type *Canvas;

Canvas canvas_create(int rows, int cols);
void canvas_destroy(Canvas c);
int canvas_get_rows(Canvas c);
int canvas_get_cols(Canvas c);
canvas_element_t canvas_get_element(Canvas c, int x, int y);
void canvas_set_element(Canvas c, int x, int y, canvas_element_t e);
void canvas_horizontal_line(Canvas c, int x, int y, int lenght,
                            canvas_element_t e);
void canvas_vertical_line(Canvas c, int x, int y, int lenght,
                          canvas_element_t e);
void canvas_box(Canvas c, int x1, int y1, int x2, int y2,
                canvas_element_t d[3]);
void canvas_draw(Canvas c);

#endif
