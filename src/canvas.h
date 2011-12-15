#ifndef CANVAS_H
#define CANVAS_H

typedef char canvas_element_t;
typedef struct canvas_type *Canvas;

Canvas canvas_create(int rows, int cols);
void canvas_destroy(Canvas c);

#endif
