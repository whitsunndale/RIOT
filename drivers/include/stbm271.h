#ifndef STBM271_H
#define STBM271_H

#include "periph/gpio.h"

typedef struct
{
    gpio_t output1;
    gpio_t output2;
} stbm271_params_t;

typedef struct {
    stbm271_params_t params;
    int offset2;
    int offset1;
    uint32_t ticks; // TODO this need to be protected by a mutex
    uint32_t start_falling;
    int last_low_ratio; // this too
} stbm271_t;


int stbm271_read_output1(stbm271_t * dev);
int stbm271_read_output2(stbm271_t * dev);
void stbm271_init(stbm271_t * dev, const stbm271_params_t *params);

#endif // STBM271_H
