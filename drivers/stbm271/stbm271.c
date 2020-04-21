#include "stbm271.h"
#include "xtimer.h"
#include "periph/gpio.h"
#include "thread.h"

#define OUTPUT1 (dev->params.output1)
#define OUTPUT2 (dev->params.output2)

char coumpute_ratio_stack[THREAD_STACKSIZE_DEFAULT];

static void _falling(void * args);

static void _rising(void * args) {
    stbm271_t * dev = (stbm271_t *) args;
    // printf("rising\n");
    dev->ticks += (xtimer_now().ticks32 - dev->start_falling);
    gpio_init_int(OUTPUT1, GPIO_IN, GPIO_FALLING, _falling, dev);
}

static void _falling(void * args) {
    stbm271_t * dev = (stbm271_t *) args;
    // printf("falling\n");
    xtimer_ticks32_t start = xtimer_now();
    dev->start_falling = start.ticks32;
    gpio_init_int(OUTPUT1, GPIO_IN, GPIO_RISING, _rising, dev);
}

static void * _compute_low_ratio(void * args){
    stbm271_t * dev = (stbm271_t *) args;
    xtimer_ticks32_t last_wakeup = xtimer_now();
    uint32_t period = 30000000;
    while(1){
        // printf("ticks : %d\n", dev->ticks);
        dev->last_low_ratio = ((float) xtimer_usec_from_ticks(xtimer_ticks(dev->ticks)) / (float)period)*100 ; //TODO Change to look-up table to run faster and without fpu
        dev->ticks = 0;
        xtimer_periodic_wakeup(&last_wakeup, period);
    }
    return NULL;
}

int stbm271_read_output1(stbm271_t * dev){
    return dev->last_low_ratio;
}

int stbm271_read_output2(stbm271_t * dev){
    return dev->last_low_ratio;
}



void stbm271_init(stbm271_t * dev, const stbm271_params_t *params){
    xtimer_init();
    dev->params = *params;
    dev->ticks = 0;
    dev->start_falling=0;
    dev->last_low_ratio=0;

    // Thread for storing low ratio every 30s
    thread_create(coumpute_ratio_stack, sizeof(coumpute_ratio_stack),
                    THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_STACKTEST,
                    _compute_low_ratio,
                    dev, "stbm271_ratio_computer");


    _rising((void *) dev);
}