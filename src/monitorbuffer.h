#ifndef MONITORBUFFER_H
#define MONITORBUFFER_H

#define buf_element_t char
#define BUFFER_MAX_SIZE 50

typedef struct {
    int count, size, number_of_readers;
    buf_element_t *data;
    pthread_mutex_t mtx_write, mtx_read;
} buffer_t;

int buffer_init(buffer_t *b, int size);

void buffer_append(buffer_t *b, buf_element_t value);

int buffer_read(buffer_t *b, buf_element_t *dest);

void buffer_clean(buffer_t *b);

void buffer_free(buffer_t *b);

#endif /* MONITORBUFFER_H */
