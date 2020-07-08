#pragma once

#include "driver/pcnt.h"
#include <stdint.h>

typedef struct {
	gpio_num_t gpioPinA, gpioPinB;
	pcnt_unit_t pcntUnit;
	uint8_t startingOffset;
} Encoder;

Encoder encoder_make(gpio_num_t gpioPinA, gpio_num_t gpioPinB);
void encoder_init(Encoder * encoder);
int32_t encoder_get_value(Encoder * encoder);
int8_t encoder_get_addition(Encoder * encoder);