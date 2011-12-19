#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

typedef struct buffer_rw_t {
    int count, size, number_of_readers;
    buf_element_t *data;
    pthread_mutex_t mtx_write, mtx_read;
};


int buffer_rw_create(int size)
{
    BufferRW b = malloc(sizeof(struct buffer_rw_t));
    if (b == NULL) {
        perror("buffer_rw_create: can't create BufferRW");
        return NULL;
    }

    b->count = b->number_of_readers = 0;
    b->size = size;

    b->data = (buf_element_t *) malloc(sizeof(buf_element_t) * size);
    if (b->data == NULL) {
        perror("buffer_rw_create: can't allocate memory for buffer data");
        return NULL;
    }

    pthread_mutex_init(&b->mtx_write, NULL);
    pthread_mutex_init(&b->mtx_read, NULL);

    return b;
}

void buffer_rw_append(BufferRW b, buf_element_t value)
{
    pthread_mutex_lock(&b->mtx_write);
    b->data[b->count] = value;
    b->count++;
    pthread_mutex_unlock(&b->mtx_write);
}

int buffer_rw_read(BufferRW b, buf_element_t *dest)
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
