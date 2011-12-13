#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char ch = 0;

void * input_thread(void *arg)
{
    while(true) {
        ch = getch();
    }
    return 0;
}

int main(void)
{
    pthread_t thr;
    int s;
    unsigned short row, col;
    
    s = pthread_create(&thr, NULL, input_thread, NULL);
    if (s != 0) {
        perror("Error in pthread_create.");
    }

    get_terminal_size(&row, &col);
    printf("Message from main()\n");
    printf("row: %hd col %hd\n", row, col);

//     while (true) {
//         printf("%c\n", ch);
//         if (ch == 113) { // q pressed
//             break;
//         } else {
//             continue;
//         }
//     }

    exit(EXIT_SUCCESS);
}
