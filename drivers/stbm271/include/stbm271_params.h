#include "board.h"
#include "stbm271.h"

/**
 * @brief   Default configuration parameters for stbm271 sensor
 * @{
 */
#ifndef STBM271_PARAM_GPIO1
#define STBM271_PARAM_GPIO1        (GPIO34)
#endif
#ifndef STBM271_PARAM_GPIO2
#define STBM271_PARAM_GPIO2       (GPIO35)
#endif

#ifndef STBM271_PARAMS
#define STBM271_PARAMS           { .output1  = STBM271_PARAM_GPIO1, \
                                  .output2 = STBM271_PARAM_GPIO2 }
#endif
/** @} */

/**
 * @brief   Allocation of stbm271 configuration
 */
static const stbm271_params_t stbm271_params[] = {
    STBM271_PARAMS
}