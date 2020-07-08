#include "Encoder.h"
// from https://github.com/espressif/esp-idf/blob/93a8603c545fb8e54741d6685146e2f3b874378d/examples/peripherals/pcnt/main/pcnt_example_main.c

#include "driver/periph_ctrl.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "esp_attr.h"
#include "esp_log.h"


Encoder encoder_make(gpio_num_t gpioPinA, gpio_num_t gpioPinB) {
	Encoder encoder;
	encoder.gpioPinA = gpioPinA;
	encoder.gpioPinB = gpioPinB;
	encoder.pcntUnit = PCNT_UNIT_0;
	return encoder;
}

void encoder_init(Encoder * encoder) {
	gpio_set_pull_mode(encoder->gpioPinA, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(encoder->gpioPinB, GPIO_PULLUP_ONLY);

	/* Prepare configuration for the PCNT unit */
	pcnt_config_t pcnt_config;

	pcnt_config.pulse_gpio_num = encoder->gpioPinA;
	pcnt_config.ctrl_gpio_num = encoder->gpioPinB;
	pcnt_config.channel = PCNT_CHANNEL_0;
	pcnt_config.unit = encoder->pcntUnit;

	// What to do on the positive / negative edge of pulse input?
	pcnt_config.pos_mode = PCNT_COUNT_INC;   // Count up on the positive edge
	pcnt_config.neg_mode = PCNT_COUNT_DIS;   // Keep the counter value on the negative edge

	// What to do when control input is low or high?
	pcnt_config.lctrl_mode = PCNT_MODE_REVERSE; // Reverse counting direction if low
	pcnt_config.hctrl_mode = PCNT_MODE_KEEP;    // Keep the primary counter mode if high

	// Set the maximum and minimum limit values to watch
	pcnt_config.counter_h_lim = 32767;
	pcnt_config.counter_l_lim = -32768; 

	
	/* Initialize PCNT unit */
	pcnt_unit_config(&pcnt_config);

	/* Configure and enable the input filter */
	pcnt_set_filter_value(encoder->pcntUnit, 1023);
	pcnt_filter_enable(encoder->pcntUnit);

	/* Enable events on overflow */
	pcnt_event_enable(encoder->pcntUnit, PCNT_EVT_H_LIM);
	pcnt_event_enable(encoder->pcntUnit, PCNT_EVT_L_LIM);

	/* Initialize PCNT's counter */
	pcnt_counter_pause(encoder->pcntUnit);
	pcnt_counter_clear(encoder->pcntUnit);

	/* Register ISR handler and enable interrupts for PCNT unit */
	//pcnt_isr_register(pcnt_example_intr_handler, NULL, 0, &user_isr_handle);
	//pcnt_intr_enable(PCNT_TEST_UNIT);

	/* Everything is set up, now go to counting */
	pcnt_counter_resume(encoder->pcntUnit);

	encoder->startingOffset = encoder_get_addition(encoder);
}

int32_t encoder_get_value(Encoder * encoder) {
	int16_t value;
	pcnt_get_counter_value(encoder->pcntUnit, &value);
	return (((int32_t) value) << 2)
			+ (int32_t) encoder_get_addition(encoder)
			- (int32_t) encoder->startingOffset;
}

// note this math is wrong!
int8_t encoder_get_addition(Encoder * encoder) {
	int8_t A = gpio_get_level(encoder->gpioPinA);
	int8_t B = gpio_get_level(encoder->gpioPinB);
	int8_t addition = (B << 1) + (A ^ B);
	return addition;
}

