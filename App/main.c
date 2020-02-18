
#include <stdio.h>

#include "xtimer.h"

int main(void)
{

    puts("My app");
    int low_ratio = 12345;
    /* get interfaces and print their addresses */
    while (1) {

        printf("Last low_ratio %d\n", low_ratio);
        xtimer_sleep(30);
    }

    /* main thread exits */
    return 0;
}
