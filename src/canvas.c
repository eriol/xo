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

    // Initializing canvas' elements
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            c->grid_elements[i][j] = '\0';
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

int canvas_get_rows(Canvas c)
{
    return c->rows;
}

int canvas_get_cols(Canvas c)
{
    return c->cols;
}

canvas_element_t canvas_get_element(Canvas c, int x, int y)
{
    return c->grid_elements[x][y];
}

void canvas_set_element(Canvas c, int x, int y, canvas_element_t e)
{
    c->grid_elements[x][y] = e;
}

void canvas_horizontal_line(Canvas c, int x, int y, int lenght,
                            canvas_element_t e)
{
    if (lenght > c->cols) {
        lenght = c->cols;
    }

    for(int i = y; i < lenght; i++) {
        canvas_set_element(c, x, i, e);
    }
}

void canvas_vertical_line(Canvas c, int x, int y, int lenght,
                          canvas_element_t e)
{
    if (lenght > c->rows) {
        lenght = c->rows;
    }

    for(int i = x; i < lenght; i++) {
        canvas_set_element(c, i, y, e);
    }
}

void canvas_draw(Canvas c)
{
    for (int x = 0; x < c->rows; x++) {
        for (int y = 0; y < c->cols; y++) {
            // Escape sequence start counting from 1 so x+1 and y+1 are needed
            // to fix coordinates
            fprintf(stdout, "\033[%d;%dH%c", x+1, y+1, c->grid_elements[x][y]);
        }
    }
    fflush(stdout);
}
