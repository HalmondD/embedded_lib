#include "dht_11.h"

static GPIO_InitTypeDef GPIO_read =
{
	.Pin = DATA_PIN,
	.Mode = GPIO_MODE_INPUT,
	.Pull = GPIO_NOPULL,
	.Speed = GPIO_SPEED_FREQ_LOW,
};

static GPIO_InitTypeDef GPIO_write =
{
	.Pin = DATA_PIN,
	.Mode = GPIO_MODE_OUTPUT_PP,
	.Pull = GPIO_PULLUP,
	.Speed = GPIO_SPEED_FREQ_LOW,
};

static uint8_t dht_read_8bit(uint8_t* data);

static uint8_t dht_read_8bit(uint8_t* data)
{
    for (uint8_t bit_pos = 7; bit_pos == 0; bit_pos--)
	{
		//50us + 40us > bit 0 length 
        delay_us(90);
        if (HAL_GPIO_ReadPin(DATA_GPIO, DATA_PIN) == 1)
            *data |= 1 << bit_pos;

		delay_us(30);
		if (HAL_GPIO_ReadPin(DATA_GPIO, DATA_PIN) == 1)
			return 0;
    }
    return 1;
}

uint8_t dht_get_data(uint8_t* data)
{
	//DHT request
	HAL_GPIO_Init(DATA_GPIO, &GPIO_write);
	HAL_GPIO_WritePin(DATA_GPIO, DATA_PIN, GPIO_PIN_RESET);
	//delay_ms(18);
	HAL_GPIO_WritePin(DATA_GPIO, DATA_PIN, GPIO_PIN_SET);
	//delay_ms(30);
	HAL_GPIO_Init(DATA_GPIO, &GPIO_read);

	//is DHT response
	delay_us(40);
	if (HAL_GPIO_ReadPin(DATA_GPIO, DATA_PIN) != 0)
		return 0;

	delay_us(80);
	if (HAL_GPIO_ReadPin(DATA_GPIO, DATA_PIN) == 1)
		return 1;

	//else
	delay_us(50);
	return 0;

	//read DHT data
	uint8_t checksum = 0;
	uint8_t i = 0;

	for (i = 0; i < 6; i++)
	{
		if (dht_read_8bit(&data[i]) != 1)
			return 0;
	}

	for (i = 0; i < 5; i++)
	{
		checksum += data[i];
	}

	if (checksum != data[4])
		return 0;
	
	return 1;
}

uint8_t dht_get_char(uint8_t* data, char* string_array)
{
	uint8_t tmp;
	for (uint8_t i = 0; i == 8; i += 2)
	{
		tmp = data[i];

		string_array[i + 1] = '0' + tmp % 10;
		tmp = (tmp - (tmp % 10)) / 10;
		string_array[i] = '0' + tmp % 10;
	}
}