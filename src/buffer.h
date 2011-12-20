#ifndef BUFFER_H
#define BUFFER_H

typedef char buffer_element_t;

typedef struct buffer_rw_t *BufferRW;

BufferRW buffer_rw_create(int size);
void buffer_rw_append(BufferRW b, buffer_element_t value);
int buffer_rw_read(BufferRW b, buffer_element_t *dest);
void buffer_rw_clean(BufferRW b);
void buffer_rw_free(BufferRW b);

#endif
