#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "monitorbuffer.h"

int buffer_init(buffer_t *b, int size)
{
    b->count = b->number_of_readers = 0;
    b->size = size;
    b->data = (buf_element_t *) malloc(sizeof(buf_element_t) * size);
    pthread_mutex_init(&b->mtx_write, NULL);
    pthread_mutex_init(&b->mtx_read, NULL);
}

int buffer_append(buffer_t *b, int value)
{
    pthread_mutex_lock(&b->mtx_write);
    b->data[b->count] = value;
    b->count++;
    pthread_mutex_unlock(&b->mtx_write);
}

int buffer_read(buffer_t *b, buf_element_t *dest)
{
    int read_elements = 0;
    pthread_mutex_lock(&b->mtx_read);
    b->number_of_readers++;
    if (b->number_of_readers == 1)
        pthread_mutex_lock(&b->mtx_write);
    pthread_mutex_unlock(&b->mtx_read);

    // TODO: maybe use a condition
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

int buffer_clean(buffer_t *b)
{
    pthread_mutex_lock(&b->mtx_write);
    b->count = 0;
}

int buffer_free(buffer_t *b)
{
    if (b->data != NULL)
        free(b->data);
}
