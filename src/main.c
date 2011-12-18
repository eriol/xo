#include <locale.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "canvas.h"
#include "monitorbuffer.h"
#include "terminal.h"
#include "xo.h"

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
    setlocale(LC_ALL, "");
    Canvas canvas, collision;
    pthread_t thr;
    int s, res;
    unsigned short rows, cols;
    buf_element_t local_buffer[BUFFER_MAX_SIZE];

    buffer_init(&input_buffer, BUFFER_MAX_SIZE);

//     s = pthread_create(&thr, NULL, input_thread, NULL);
//     if (s != 0) {
//         perror("Error in pthread_create.");
//     }

    terminal_get_size(&rows, &cols);
    canvas = canvas_create(rows, cols);
    collision = canvas_create(rows, cols);

//     xo_intro(canvas);
    xo_draw_game_layout(canvas, collision);


    res = xo_insert_bunch_creatures(canvas, collision, true, 15);
    res = xo_insert_bunch_creatures(canvas, collision, false, 15);

    canvas_draw(canvas);
//     canvas_draw(collision);

    while (true) {
        sleep(10);
    }

//     canvas_destroy(canvas);
//     exit(EXIT_SUCCESS);
}
