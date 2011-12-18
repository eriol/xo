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
    int s, res, inserted_creature[] = {0, 0};
    unsigned short rows, cols;
    buf_element_t local_buffer[BUFFER_MAX_SIZE];

    buffer_init(&input_buffer, BUFFER_MAX_SIZE);

    // Initialize random seed
    srandom(time(NULL));

//     s = pthread_create(&thr, NULL, input_thread, NULL);
//     if (s != 0) {
//         perror("Error in pthread_create.");
//     }

    terminal_get_size(&rows, &cols);
    canvas = canvas_create(rows, cols);
    collision = canvas_create(rows, cols);

//     xo_intro(canvas);
    xo_draw_game_layout(canvas, collision);
    xo_draw_creature(canvas, collision, 1, 1, true);
    xo_draw_bunch_creatures(canvas, collision, true, 4);
    xo_draw_creature_random_point(canvas, collision, true);
    xo_draw_random_creatures(canvas, collision, 20, inserted_creature);
    xo_draw_the_chosen_one(canvas, collision, true);
    xo_draw_life(canvas, 3);
    xo_draw_timebar100(canvas, 50);

    canvas_draw(canvas);
//     sleep(1);
//     canvas_draw(collision);

    while (true) {
        sleep(10);
    }

    canvas_destroy(canvas);
    exit(EXIT_SUCCESS);
}
