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

#ifndef BUFFER_H
#define BUFFER_H

typedef char buffer_rw_element_t;
typedef int buffer_pc_element_t;

typedef struct buffer_rw_t *BufferRW;
typedef struct buffer_pc_t *BufferPC;

BufferRW buffer_rw_create(int size);
void buffer_rw_append(BufferRW b, buffer_rw_element_t value);
int buffer_rw_read(BufferRW b, buffer_rw_element_t *dest);
void buffer_rw_clean(BufferRW b);
void buffer_rw_free(BufferRW b);

BufferPC buffer_pc_create(int size);
void buffer_pc_put(BufferPC b, buffer_pc_element_t value);
void buffer_pc_get(BufferPC b, buffer_pc_element_t *value);
void buffer_pc_free(BufferPC b);

#endif
