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
#include "utils.h"
#include "xo.h"

#define BUFFER_RW_MAX_SIZE 10

void *input_controller(void *arg);
void *game_controller(void *arg);
void *brain(void *);

BufferRW input_buffer;
BufferPC brain_buffer;

Canvas canvas, collision;

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    bool intro_flag = true, sound_flag = false;
    int s, opt;
    pthread_t thr_input_controller, thr_game_controller, thr_brain;
    unsigned short rows, cols;
    buffer_rw_element_t local_buffer[BUFFER_RW_MAX_SIZE];

    input_buffer = buffer_rw_create(BUFFER_RW_MAX_SIZE);
    brain_buffer = buffer_pc_create(1);

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

//     s = pthread_create(&thr_input_controller, NULL, input_controller, NULL);
//     if (s != 0) {
//         perror("pthread_create: failed to create thr_input_controller");
//     }
    s = pthread_create(&thr_game_controller, NULL, game_controller, NULL);
    if (s != 0) {
        perror("pthread_create: failed to create thr_game_controller");
    }
    s = pthread_create(&thr_brain, NULL, brain, NULL);
    if (s != 0) {
        perror("pthread_create: failed to create thr_brain");
    }

    while (true) {
        #ifdef TEST
        int res;
        res = buffer_rw_read(input_buffer, local_buffer);
        if (res > 0) {
            printf("%d\n", atoi(local_buffer));
            printf("%d\n", res);
        }
        for (int i = 0; i < BUFFER_RW_MAX_SIZE; i++)
            local_buffer[i] = 0;
        int creature = 20;
        printf("In main...\n");
        buffer_pc_get(brain_creature_type_buffer, &creature);
        printf("Creature: %d\n", creature);
        #endif
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
    int life = 3, num_creatures;
    int inserted_creature[] = {0, 0};
    buffer_pc_element_t creature_type;

    while(true) {
        canvas_clean(canvas);
        canvas_clean(collision);
        xo_draw_game_layout(canvas, collision);

        buffer_pc_get(brain_buffer, &creature_type);
        xo_draw_the_chosen_one(canvas, collision, (bool) creature_type);

        buffer_pc_get(brain_buffer, &num_creatures);
        xo_draw_random_creatures(canvas, collision, num_creatures,
                                 inserted_creature);

        xo_draw_life(canvas, life);
        xo_draw_timebar100(canvas, 100, NULL);
        canvas_draw(canvas);
        sleep(1);
    }

}

void *brain(void *arg)
{
    int creature_type, start_creatures = randrange(1, 20);

    while(true) {
        creature_type = randrange(0, 1);
        buffer_pc_put(brain_buffer, creature_type);
        buffer_pc_put(brain_buffer, start_creatures);
    }
}
