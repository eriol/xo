#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "monitorbuffer.h"
#include "terminal.h"



buffer_t input_buffer;

void * input_thread(void *arg)
{
    char ch = 0;
    while(true) {
        ch = getch();
        buffer_append(&input_buffer, ch);
    }
    return 0;
}

int main(void)
{
    pthread_t thr;
    int s, res;
    unsigned short row, col;
    buf_element_t local_buffer[BUFFER_MAX_SIZE];

    buffer_init(&input_buffer, BUFFER_MAX_SIZE);

    s = pthread_create(&thr, NULL, input_thread, NULL);
    if (s != 0) {
        perror("Error in pthread_create.");
    }

    terminal_clear();
    terminal_get_size(&row, &col);
    printf("Message from main()\n");
    printf("row: %hd col %hd\n", row, col);

    while (true) {
        res = buffer_read(&input_buffer, local_buffer);
        if (res > 0) {
            printf("%d\n", atoi(local_buffer));
            printf("%d\n", res);
        }
    }

    exit(EXIT_SUCCESS);
}
