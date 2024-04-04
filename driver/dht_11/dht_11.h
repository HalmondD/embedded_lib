#ifndef DHT_11_DHT_11_H_
#define DHT_11_DHT_11_H_

#include <stdint.h>

#include "stm32f1xx_hal.h"
#include "util.h"

#define DATA_GPIO	GPIOA
#define DATA_PIN	GPIO_PIN_13

void delay_ms(uint32_t delay_time_ms);

#endif /* DHT_11_DHT_11_H_ */
