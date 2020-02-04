#include "stbm271.h"
#include "xtimer.h"
#include "gpio.h"

#define OUTPUT1 (dev->params.output1)
#define OUTPUT2 (dev->params.output2)

void _rising(void * args) {
    stbm271_t * dev = (stbm271_t *) args;
    gpio_init_int(OUTPUT1, GPIO_IN, GPIO_RISING, _falling, dev);
}

void _falling(void * args) {
    stbm271_t * dev = (stbm271_t *) args;
    xtimer_ticks32_t start = xtimer_now();
    gpio_init_int(OUTPUT1, GPIO_IN, GPIO_RISING, _rising, dev);
}


int stbm271_read_output1(stbm271_t * dev){
    
}

int stbm271_read_output2(stbm271_t * dev){

}

void stbm271_init(stbm271_t * dev){
    xtimer_init();
    gpio_init_int(OUTPUT1, GPIO_IN, GPIO_FALLING, _falling, dev);
}