#ifndef PIR_AM312_H
#define PIR_AM312_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

void pir_am312_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t pir_get_data(void);

#endif /*PIR_AM312_H*/
