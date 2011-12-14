#ifndef MONITORBUFFER_H
#define MONITORBUFFER_H

#include <pthread.h>

#define buf_element_t int
#define BUFFER_MAX_SIZE 50

typedef struct {
    int count, size, number_of_readers;
    buf_element_t *data;
    pthread_mutex_t mtx_write, mtx_read;
} buffer_t;

int buffer_init(buffer_t *b, int size);

int buffer_append(buffer_t *b, int value);

int buffer_get_actual_data_size(buffer_t *b);

int buffer_read(buffer_t *b, int *dest);

int buffer_clean(buffer_t *b);

#endif /* MONITORBUFFER_H */
