#ifndef CANVAS_H
#define CANVAS_H

typedef char canvas_element_t;
typedef struct canvas_type *Canvas;

Canvas canvas_create(int rows, int cols);
void canvas_destroy(Canvas c);
int canvas_get_rows(Canvas c);
int canvas_get_cols(Canvas c);
canvas_element_t canvas_get_element(Canvas c, int x, int y);
void canvas_set_element(Canvas c, int x, int y, canvas_element_t e);
void canvas_horizontal_line(Canvas c, int x, int y, int lenght,
                            canvas_element_t e);
void canvas_draw(Canvas c);

#endif
