#ifndef LM_393_H
#define LM_393_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

void lm393_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t lm393_get_data(void);

#endif /* LM393_H */
