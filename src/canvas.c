#include <stdio.h>
#include <stdlib.h>

#include "canvas.h"

struct canvas_type {
    int rows;
    int cols;
    canvas_element_t **grid_elements;
};

Canvas canvas_create(int rows, int cols)
{
    Canvas c = malloc(sizeof(struct canvas_type));
    if (c == NULL) {
        perror("canvas_create: can't create canvas");
        return NULL;
    }
    c->rows = rows;
    c->cols = cols;
    // Allocating rows array for grid_elements
    c->grid_elements = malloc(rows * sizeof(canvas_element_t *));

    if (c->grid_elements == NULL) {
        perror("canvas_create: can't allocate rows array");
        free(c);
        return NULL;
    }

    // Allocating cols array for each row
    for (int i = 0; i < rows; i++) {
        c->grid_elements[i] = malloc(cols * sizeof(canvas_element_t));

        if (c->grid_elements[i] == NULL) {
            perror("canvas_create: can't allocate col array");
            for (int j = --i; j >= 0; j--) {
                free(c->grid_elements[j]);
            }
            return NULL;
        }
    }

    return c;

}

void canvas_destroy(Canvas c)
{
    // Deallocating cols array for each row
    for (int i = 0; i < c->rows; i++) {
        free(c->grid_elements[i]);
    }
    // Deallocating rows array
    free(c->grid_elements);
    // Destroy!
    free(c);
}
