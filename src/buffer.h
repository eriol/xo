#ifndef BUFFER_H
#define BUFFER_H

#define buf_element_t char

typedef struct buffer_rw_t *BufferRW;

int buffer_rw_init(BufferRW b, int size);
void buffer_rw_append(BufferRW b, buf_element_t value);
int buffer_rw_read(BufferRW b, buf_element_t *dest);
void buffer_rw_clean(BufferRW b);
void buffer_rw_free(BufferRW b);

#endif
