/*
 * Copyright 2011 Daniele Tricoli <eriol@mornie.org>
 *
 * This file is part of xo.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see http://www.gnu.org/licenses/.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "canvas.h"
#include "utils.h"


#define OPTION_SIZE 3


struct canvas_type {
    int rows;
    int cols;
    canvas_element_t **grid_elements;
    bool advanced_options;
    int ***option_map;
};


Canvas canvas_create(int rows, int cols, bool advanced_options)
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
        return NULL;
    }

    // Allocating cols array for each row
    for (int i = 0; i < rows; i++) {
        c->grid_elements[i] = malloc(cols * sizeof(canvas_element_t));

        if (c->grid_elements[i] == NULL) {
            perror("canvas_create: can't allocate col array");
            return NULL;
        }

    }

    c->advanced_options = advanced_options;

    if (advanced_options) {
        c->option_map = malloc(rows * sizeof(int **));
        if (c->option_map == NULL) {
            perror("canvas_create: can't allocate option rows array");
            return NULL;
        }

        for (int i = 0; i < rows; i++) {
            c->option_map[i] = malloc(cols * sizeof(int *));

            if (c->option_map[i] == NULL) {
                perror("canvas_create: can't allocate option col array");
                return NULL;
            }

            for (int j = 0; j < cols; j++) {
                c->option_map[i][j] = malloc(OPTION_SIZE * sizeof(int));

                if (c->option_map[i][j] == NULL) {
                    perror("canvas_create: can't allocate options array");
                    return NULL;
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

    if (c->advanced_options) {
        for (int i = 0; i < c->rows; i++) {
            for (int j = 0; j < c->cols; j++) {
                for (int k = 0; k < OPTION_SIZE; k++) {
                    c->option_map[i][j][k] = 0;
                }
            }
        }
    }
}

void canvas_destroy(Canvas c)
{
    // cols array for each row
    for (int i = 0; i < c->rows; i++) {
        free(c->grid_elements[i]);
    }
    // rows array
    free(c->grid_elements);


    if (c->advanced_options) {
        for (int i = 0; i < c->rows; i++) {
            for (int j = 0; j < c->cols; j++) {
                // options array
                free(c->option_map[i][j]);
            }
            // cols array for each row
            free(c->option_map[i]);
        }
        // rows array
        free(c->option_map);
    }

    // Engage photon torpedoes. Fire!
    free(c);
}

bool canvas_has_advanced_options(Canvas c)
{
    return c->advanced_options;
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
    if (x < c->rows && x >= 0 && y < c->cols && y >= 0) {
        c->grid_elements[x][y] = e;
    }
}

void canvas_set_element_options(Canvas c, int x, int y, int *options)
{
    if (x < c->rows && x >= 0 && y < c->cols && y >= 0) {
        for (int i = 0; i < OPTION_SIZE; i++)
            c->option_map[x][y][i] = options[i];
    }
}

void canvas_get_element_options(Canvas c, int x, int y, int *options)
{
    if (x < c->rows && x >= 0 && y < c->cols && y >= 0) {
        for (int i = 0; i < OPTION_SIZE; i++)
            options[i] = c->option_map[x][y][i];
    }
}

void canvas_horizontal_line(Canvas c, int x, int y, int lenght,
                            canvas_element_t e, int* options)
{
    if (lenght > c->cols) {
        lenght = c->cols;
    }

    for(int i = 0; i < lenght; i++) {
        canvas_set_element(c, x, y + i, e);

        if (c->advanced_options && options != NULL) {
            canvas_set_element_options(c, x, y + i, options);
        }
    }
}

void canvas_vertical_line(Canvas c, int x, int y, int lenght,
                          canvas_element_t e, int* options)
{
    if (lenght > c->rows) {
        lenght = c->rows;
    }

    for(int i = 0; i < lenght; i++) {
        canvas_set_element(c, x + i, y, e);

        if (c->advanced_options && options != NULL) {
            canvas_set_element_options(c, x + i, y, options);
        }
    }
}

void canvas_box(Canvas c, int x1, int y1, int x2, int y2, canvas_element_t *d,
                int *horizontal_options, int *vertical_options,
                int *corners_options)
{
        // Up
        canvas_horizontal_line(c, x1, y1, y2, d[0], horizontal_options);
        // Bottom
        canvas_horizontal_line(c, x2, y1, y2, d[0], horizontal_options);
        // Left
        canvas_vertical_line(c, x1, y1, x2, d[1], vertical_options);
        // Right
        canvas_vertical_line(c, x1, y2, x2, d[1], vertical_options);
        //Corners clockwise order
        canvas_set_element(c, x1, y1, d[2]);
        canvas_set_element(c, x1, y2, d[2]);
        canvas_set_element(c, x2, y2, d[2]);
        canvas_set_element(c, x2, y1, d[2]);

        if (c->advanced_options && corners_options != NULL) {
            canvas_set_element_options(c, x1, y1, corners_options);
            canvas_set_element_options(c, x1, y2, corners_options);
            canvas_set_element_options(c, x2, y2, corners_options);
            canvas_set_element_options(c, x2, y1, corners_options);
        }
}

void canvas_box_fill(Canvas c, int x1, int y1, int x2, int y2,
                     canvas_element_t d, int *options)
{
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            canvas_set_element(c, i, j, d);

            if (c->advanced_options && options != NULL) {
                canvas_set_element_options(c, i, j, options);
            }

        }
    }
}

void canvas_border(Canvas c, canvas_element_t *d, int *horizontal_options,
                   int *vertical_options, int *corners_options)
{
    canvas_box(c, 0, 0, c->rows - 1, c->cols - 1, d, horizontal_options,
               vertical_options, corners_options);
}

void canvas_draw(Canvas c)
{
    for (int x = 0; x < c->rows; x++) {
        for (int y = 0; y < c->cols; y++) {
            if (c->advanced_options) {
                if (c->option_map[x][y][2] > 0)
                    fwprintf(stdout, L"\033[%d;%d;%dm", c->option_map[x][y][0],
                                                        c->option_map[x][y][1],
                                                        c->option_map[x][y][2]);
                else
                    fwprintf(stdout, L"\033[%d;%dm", c->option_map[x][y][0],
                                                     c->option_map[x][y][1]);
            }
            // Terminal starts from 1 so x + 1 and y + 1 are needed to fix
            // coordinates
            fwprintf(stdout, L"\033[%d;%dH%lc", x + 1, y + 1,
                     c->grid_elements[x][y]);
            if (c->advanced_options)
                fwprintf(stdout, L"\033[%dm", 0);
        }
    }
    fflush(stdout);
}

int random_fcolor(void)
{
    return randrange(F_BLACK, F_WHITE);
}

int random_bcolor(void)
{
    return randrange(B_BLACK, B_WHITE);
}
