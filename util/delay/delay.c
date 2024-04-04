#include "delay.h"
#include <stdint.h>

volatile uint8_t delay_update_flag = 0;

void delay_us(uint16_t delay_time_us)
{
    // Util use SysTick
    #if (UTIL_TIMEBASE == 0)
        delay_update_flag = 0;
        /*
        * Do ham HAL_SYSTICK_config luon mac dinh lay clock la AHB khong chia cho 8
        * nen, T = 1 / 8*10^6 = 1.25*10^-7, de co tick cho 1us thi SysTick_load = 1*10^-6/1.25*10-7 = 8
        */
        uint32_t systick_load = delay_time_us * 8;
        HAL_SYSTICK_Config(systick_load);
        while (delay_update_flag == 0);

   #elif (UTIL_TIMEBASE == 1)
    // Util use Timer
        UTIL_TIMEBASE_SOURCE.Init.Prescaler = 8 - 1;
        UTIL_TIMEBASE_SOURCE.Init.Period = delay_time_us;
        HAL_TIM_Base_Init(&UTIL_TIMEBASE_SOURCE);

        HAL_TIM_Base_Start(&UTIL_TIMEBASE_SOURCE);
        UTIL_TIMEBASE_SOURCE.Instance->CNT = 0;
        while (UTIL_TIMEBASE_SOURCE.Instance->CNT < delay_time_us);
        HAL_TIM_Base_Stop(&UTIL_TIMEBASE_SOURCE);

    #endif
}

void delay_ms(uint16_t delay_time_ms)
{   
    // Util use SysTick
    #if (UTIL_TIMEBASE == 0)
        delay_update_flag = 0;
        /*
        * Do ham HAL_SYSTICK_config luon mac dinh lay clock la AHB khong chia cho 8
        * nen, T = 1 / 8*10^6 = 1.25*10^-7, de co tick cho 1ms thi SysTick_load = 1*10^-3/1.25*10-7 = 8000
        */
        uint32_t systick_load = delay_time_ms * 8000;
        HAL_SYSTICK_Config(systick_load);
        while (delay_update_flag == 0);

    #elif (UTIL_TIMEBASE == 1)
    // Util use Timer
        UTIL_TIMEBASE_SOURCE.Init.Prescaler = 8000 - 1;
        UTIL_TIMEBASE_SOURCE.Init.Period = delay_time_ms;
        HAL_TIM_Base_Init(&UTIL_TIMEBASE_SOURCE);

        HAL_TIM_Base_Start(&UTIL_TIMEBASE_SOURCE);
        UTIL_TIMEBASE_SOURCE.Instance->CNT = 0;
        while (UTIL_TIMEBASE_SOURCE.Instance->CNT < delay_time_ms);
        HAL_TIM_Base_Stop(&UTIL_TIMEBASE_SOURCE);

    #endif
}

#if (UTIL_TIMEBASE == 0)
void util_delay_handle(void)
{
    delay_update_flag = 1;
    SysTick->CTRL &= !SysTick_CTRL_ENABLE_Msk;
}
#endif
