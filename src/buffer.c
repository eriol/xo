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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

struct buffer_rw_t {
    int count, size, number_of_readers;
    buffer_rw_element_t *data;
    pthread_mutex_t mtx_write, mtx_read;
};

struct buffer_pc_t {
    int count, size;
    int head, tail;
    buffer_pc_element_t *data;
    pthread_mutex_t mtx;
    pthread_cond_t until_not_empty, until_not_full;
};

BufferRW buffer_rw_create(int size)
{
    BufferRW b = malloc(sizeof(struct buffer_rw_t));
    if (b == NULL) {
        perror("buffer_rw_create: can't create BufferRW");
        return NULL;
    }

    b->count = b->number_of_readers = 0;
    b->size = size;

    // Adding one more space to put the '\0'
    b->data = malloc(sizeof(buffer_rw_element_t) * (size + 1));
    if (b->data == NULL) {
        perror("buffer_rw_create: can't allocate memory for buffer data");
        return NULL;
    }

    pthread_mutex_init(&b->mtx_write, NULL);
    pthread_mutex_init(&b->mtx_read, NULL);

    return b;
}

void buffer_rw_append(BufferRW b, buffer_rw_element_t value)
{
    pthread_mutex_lock(&b->mtx_write);
    if (b->count < b->size) {
        b->data[b->count] = value;
        b->count++;
        b->data[b->count] = '\0';
    }
    pthread_mutex_unlock(&b->mtx_write);
}

int buffer_rw_read(BufferRW b, buffer_rw_element_t *dest)
{
    int read_elements = 0;

    pthread_mutex_lock(&b->mtx_read);
    b->number_of_readers++;
    if (b->number_of_readers == 1)
        pthread_mutex_lock(&b->mtx_write);
    pthread_mutex_unlock(&b->mtx_read);

    if (b->count > 0) {
        memcpy(dest, b->data, b->count);
        read_elements = b->count;
    }

    pthread_mutex_lock(&b->mtx_read);
    b->number_of_readers--;
    if (b->number_of_readers == 0)
        pthread_mutex_unlock(&b->mtx_write);
    pthread_mutex_unlock(&b->mtx_read);

    return read_elements;
}

void buffer_rw_clean(BufferRW b)
{
    pthread_mutex_lock(&b->mtx_write);
    b->count = 0;
    pthread_mutex_unlock(&b->mtx_write);
}

void buffer_rw_free(BufferRW b)
{
    if (b->data != NULL)
        free(b->data);

    free(b);
}

BufferPC buffer_pc_create(int size) {
    BufferPC b = malloc(sizeof(struct buffer_pc_t));
    if (b == NULL) {
        perror("buffer_pc_create: can't create BufferPC");
        return NULL;
    }

    b->count = b->head = b->tail = 0;
    b->size = size;

    b->data = malloc(sizeof(buffer_pc_element_t) * size);
    if (b->data == NULL) {
        perror("buffer_pc_create: can't allocate memory for buffer data");
        return NULL;
    }

    pthread_mutex_init(&b->mtx, NULL);
    pthread_cond_init(&b->until_not_empty, NULL);
    pthread_cond_init(&b->until_not_full, NULL);

    return b;
}

void buffer_pc_put(BufferPC b, buffer_pc_element_t value)
{
    pthread_mutex_lock(&b->mtx);
    while(b->count == b->size) {
        pthread_cond_wait(&b->until_not_empty, &b->mtx);
    }
    b->data[b->tail] = value;
    b->tail = (b->tail + 1) % b->size;
    b->count++;
    pthread_cond_broadcast(&b->until_not_full);
    pthread_mutex_unlock(&b->mtx);
}

void buffer_pc_get(BufferPC b, buffer_pc_element_t *value)
{
    pthread_mutex_lock(&b->mtx);
    while(b->count == 0) {
        pthread_cond_wait(&b->until_not_full, &b->mtx);
    }
    *value = b->data[b->head];
    b->head = (b->head + 1) % b->size;
    b->count--;
    pthread_cond_broadcast(&b->until_not_empty);
    pthread_mutex_unlock(&b->mtx);
}

void buffer_pc_free(BufferPC b)
{
    if (b->data != NULL)
        free(b->data);

    free(b);
}
