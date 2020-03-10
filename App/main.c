
#include <stdio.h>

#include "xtimer.h"
#include "stbm271.h"

int main(void)
{

    puts("My app");
    printf("xtimer scaler : %d\n", XTIMER_SHIFT);
    int low_ratio = 12345;

    stbm271_t dev;
    stbm271_init(&dev);



    do {
        printf("Last low_ratio %d\n", low_ratio);
        xtimer_sleep(30);
        low_ratio = stbm271_read_output1(&dev);
        printf("ticks : %d\n", dev.ticks);
    } while(1);

    /* main thread exits */
    return 0;
}
