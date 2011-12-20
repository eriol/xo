#include <locale.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "canvas.h"
#include "buffer.h"
#include "terminal.h"
#include "xo.h"

#define BUFFER_RW_MAX_SIZE 10

void *input_controller(void *arg);
void *game_controller(void *arg);

BufferRW input_buffer;
Canvas canvas, collision;

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    bool intro_flag = true, sound_flag = false;
    int s, opt;
    pthread_t thr_input_controller, thr_game_controller;
    unsigned short rows, cols;
    buffer_rw_element_t local_buffer[BUFFER_RW_MAX_SIZE];

    input_buffer = buffer_rw_create(BUFFER_RW_MAX_SIZE);

    // Initialize random seed
    srandom(time(NULL));

    while ((opt = getopt(argc, argv, "is")) != -1) {
        switch (opt) {
            case 'i':
                intro_flag = false;
                break;
            case 's':
                sound_flag = true;
                break;
            default:
                fprintf(stderr, "Usage: %s [-is]\n", argv[0]);
                fprintf(stderr, "    -i    Disable introduction\n");
                fprintf(stderr, "    -s    Enable sound\n");
                exit(EXIT_FAILURE);
        }
    }

    terminal_get_size(&rows, &cols);
    canvas = canvas_create(rows, cols, true);
    collision = canvas_create(rows, cols, false);

    if (intro_flag)
        xo_intro(canvas);

    s = pthread_create(&thr_input_controller, NULL, input_controller, NULL);
    if (s != 0) {
        perror("pthread_create: failed to create thr_input_controller");
    }
    s = pthread_create(&thr_game_controller, NULL, game_controller, NULL);
    if (s != 0) {
        perror("pthread_create: failed to create thr_game_controller");
    }

    while (true) {
        sleep(1);
    }

    canvas_destroy(canvas);
    exit(EXIT_SUCCESS);
}

void *input_controller(void *arg)
{
    char ch = 0;

    while(true) {
        ch = getch();

        if (ch >= '0' && ch <='9') {
            buffer_rw_append(input_buffer, ch);
        } else if (ch == ' ') {
            buffer_rw_clean(input_buffer);
        }
    }

    return 0;
}

void *game_controller(void *arg)
{
    int inserted_number = 0;
    int s, res, inserted_creature[] = {0, 0};

    while(true) {
        xo_draw_game_layout(canvas, collision);
        //     xo_draw_creature(canvas, collision, 1, 1, true, (int []) {NONE, F_RED, NONE});
        //     xo_draw_bunch_creatures(canvas, collision, true, 4);
        //     xo_draw_creature_random_point(canvas, collision, true,
        //                                   (int []) {NONE, F_GREEN, NONE});
        //     xo_draw_random_creatures(canvas, collision, 20, inserted_creature);
        //     xo_draw_the_chosen_one(canvas, collision, true);
        //     xo_draw_life(canvas, 3);
        //     xo_draw_timebar100(canvas, 50, NULL);
        canvas_draw(canvas);
        sleep(10);
    }

}
