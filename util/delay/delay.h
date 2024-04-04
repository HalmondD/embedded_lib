#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>

#include "stm32f1xx_hal.h"
#include "core_cm3.h"

/*
* 0 IF USE SYSTICK
* 1 IF USE TIMER
*/
#define UTIL_TIMEBASE   1

#if (UTIL_TIMEBASE == 1)
    #define UTIL_TIMEBASE_SOURCE    htim3
    extern TIM_HandleTypeDef UTIL_TIMEBASE_SOURCE;
#endif

#define UINT32_T_MAX 4294967295

void delay_us(uint16_t delay_time_us);
void delay_ms(uint16_t delay_time_ms);
void util_delay_handle(void);

#endif /* DELAY_H_ */
