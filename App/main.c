
#include <stdio.h>

#include "xtimer.h"
#include "stbm271.h"
// #include "stbm271_params.h"
#include "board.h"

int main(void)
{
    xtimer_sleep(10);

    puts("My app");
    int low_ratio = 12345;

    stbm271_t dev;
    stbm271_params_t param = { .output1  = GPIO18,.output2 = GPIO19 };
    stbm271_init(&dev, &param);

    do {
        printf("Last low_ratio %d\n", low_ratio);
        xtimer_sleep(30);
        low_ratio = stbm271_read_output1(&dev);
    } while(1);

    /* main thread exits */
    return 0;
}
