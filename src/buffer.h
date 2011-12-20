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
