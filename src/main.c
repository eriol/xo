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

buffer_t input_buffer;
Canvas canvas;

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
    setlocale(LC_ALL,"");
    pthread_t thr;
    int s, res;
    unsigned short rows, cols;
    buf_element_t local_buffer[BUFFER_MAX_SIZE];

    buffer_init(&input_buffer, BUFFER_MAX_SIZE);

//     s = pthread_create(&thr, NULL, input_thread, NULL);
//     if (s != 0) {
//         perror("Error in pthread_create.");
//     }

    terminal_clear();
    terminal_get_size(&rows, &cols);
//     terminal_draw_horizontal_line(1, 1, 20, '-');
//     terminal_draw_vertical_line(2, 1, 20, '|');
//     terminal_put_chat_at(1, 1, '+');

    canvas = canvas_create(rows, cols);

//     printf("canvas rows %d\n", canvas_get_rows(canvas));
//     printf("canvas cols %d\n", canvas_get_cols(canvas));
//     printf("%c\n", canvas_get_element(canvas, 1, 1));
//     canvas_set_element(canvas, 1, 1, 'x');
//     canvas_horizontal_line(canvas, 0, 0, 200, '-');
//     canvas_horizontal_line(canvas, rows - 1, 0, 200, '-');
//     canvas_vertical_line(canvas, 0, 0, 200, '|');
//     canvas_vertical_line(canvas, 0, cols - 1, 200, '|');


    canvas_layout(canvas);

    canvas_draw(canvas);
    canvas_destroy(canvas);

    while (true) {
        sleep(10);
//         res = buffer_read(&input_buffer, local_buffer);
//         if (res > 0) {
//             printf("%d\n", atoi(local_buffer));
//             printf("%d\n", res);
//         }
    }

    exit(EXIT_SUCCESS);
}
