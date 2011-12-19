#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "canvas.h"

struct canvas_type {
    int rows;
    int cols;
    canvas_element_t **grid_elements;
    bool color_enabled;
    int **color_map;
};

Canvas canvas_create(int rows, int cols, bool enable_colors)
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

    c->color_enabled = enable_colors;

    if (enable_colors) {
        c->color_map = malloc(rows * sizeof(int *));
        if (c->color_map == NULL) {
            perror("canvas_create: can't allocate color rows array");
            c->color_enabled = false;
        }

        if (c->color_map != NULL) {
            for (int i = 0; i < rows; i++) {
                c->color_map[i] = malloc(cols * sizeof(int));

                if (c->color_map[i] == NULL) {
                    perror("canvas_create: can't allocate color col array");
                    for (int j = --i; j >= 0; j--) {
                        free(c->color_map[j]);
                    }
                    c->color_enabled = false;
                }
            }
        }
    }

    canvas_clean(c);

    return c;

}

void canvas_clean(Canvas c)
{
    for (int i = 0; i < c->rows; i++) {
        for (int j = 0; j < c->cols; j++) {
            c->grid_elements[i][j] = L' ';
        }
    }

    if (c->color_map !=NULL) {
        for (int i = 0; i < c->rows; i++) {
            for (int j = 0; j < c->cols; j++) {
                c->grid_elements[i][j] = 0;
            }
        }
    }
}

void canvas_destroy(Canvas c)
{
    // Deallocating cols array for each row
    for (int i = 0; i < c->rows; i++) {
        free(c->grid_elements[i]);
    }
    // Deallocating rows array
    free(c->grid_elements);

    // Free the color_map if it exists
    if (c->color_map !=NULL) {
        for (int i = 0; i < c->rows; i++) {
            free(c->color_map[i]);
        }
        free(c->color_map);
    }

    // Engage photon torpedoes. Fire!
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
    if (x <= c->rows && x >= 0 && y <= c->cols && y >= 0) {
        c->grid_elements[x][y] = e;
    }
}

void canvas_horizontal_line(Canvas c, int x, int y, int lenght,
                            canvas_element_t e)
{
    if (lenght > c->cols) {
        lenght = c->cols;
    }

    for(int i = 0; i < lenght; i++) {
        canvas_set_element(c, x, y + i, e);
    }
}

void canvas_vertical_line(Canvas c, int x, int y, int lenght,
                          canvas_element_t e)
{
    if (lenght > c->rows) {
        lenght = c->rows;
    }

    for(int i = 0; i < lenght; i++) {
        canvas_set_element(c, x + i, y, e);
    }
}

void canvas_box(Canvas c, int x1, int y1, int x2, int y2, canvas_element_t d[3])
{
        // Up
        canvas_horizontal_line(c, x1, y1, y2, d[0]);
        // Bottom
        canvas_horizontal_line(c, x2, y1, y2, d[0]);
        // Left
        canvas_vertical_line(c, x1, y1, x2, d[1]);
        // Right
        canvas_vertical_line(c, x1, y2, x2, d[1]);
        //Corners clockwise order
        canvas_set_element(c, x1, y1, d[2]);
        canvas_set_element(c, x1, y2, d[2]);
        canvas_set_element(c, x2, y2, d[2]);
        canvas_set_element(c, x2, y1, d[2]);
}

void canvas_box_fill(Canvas c, int x1, int y1, int x2, int y2,
                     canvas_element_t d)
{
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            canvas_set_element(c, i, j, d);
        }
    }
}

void canvas_border(Canvas c, canvas_element_t d[3])
{
    canvas_box(c, 0, 0, c->rows - 1, c->cols - 1, d);
}

void canvas_draw(Canvas c)
{
    for (int x = 0; x < c->rows; x++) {
        for (int y = 0; y < c->cols; y++) {
            // Terminal starts from 1 so x + 1 and y + 1 are needed to fix
            // coordinates
            fwprintf(stdout, L"\033[%d;%dH%lc", x + 1, y + 1,
                     c->grid_elements[x][y]);
        }
    }
    fflush(stdout);
}
