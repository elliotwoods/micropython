#include "quadrature.h"

// Include required definitions first.
#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"

#include "driver/periph_ctrl.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "esp_attr.h"
#include "esp_log.h"

// this is the actual C-structure for our new object
typedef struct _quadrature_encoder_t {
	// base represents some basic information, like type
	mp_obj_base_t base;
	// a member created by us
	gpio_num_t gpioPinA, gpioPinB;
	pcnt_unit_t pcntUnit;
	int8_t startingOffset;
} quadrature_encoder_t;

mp_obj_t quadrature_encoder_make_new( const mp_obj_type_t *type,
								  size_t n_args,
								  size_t n_kw,
								  const mp_obj_t *args ) {
	// this checks the number of arguments (min 2, max 2);
	// on error -> raise python exception
	mp_arg_check_num(n_args, n_kw, 2, 2, true);
	// create a new object of our C-struct type
	quadrature_encoder_t *self = m_new_obj(quadrature_encoder_t);
	// give it a type
	
	self->base.type = &quadrature_type;
	// set the member number with the first argument of the constructor
	int pin_A = mp_obj_get_int(args[0]);
	int pin_B = mp_obj_get_int(args[1]);
	self->gpioPinA = (gpio_num_t) pin_A;
	self->gpioPinB = (gpio_num_t) pin_B;
	
	gpio_set_pull_mode(self->gpioPinA, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(self->gpioPinB, GPIO_PULLUP_ONLY);

	// Prepare configuration for the PCNT unit
	{

		pcnt_config_t pcnt_config;

		pcnt_config.pulse_gpio_num = self->gpioPinA;
		pcnt_config.ctrl_gpio_num = self->gpioPinB;
		pcnt_config.channel = PCNT_CHANNEL_0;
		pcnt_config.unit = self->pcntUnit;

		// What to do on the positive / negative edge of pulse input?
		pcnt_config.pos_mode = PCNT_COUNT_INC;   // Count up on the positive edge
		pcnt_config.neg_mode = PCNT_COUNT_DIS;   // Keep the counter value on the negative edge

		// What to do when control input is low or high?
		pcnt_config.lctrl_mode = PCNT_MODE_REVERSE; // Reverse counting direction if low
		pcnt_config.hctrl_mode = PCNT_MODE_KEEP;    // Keep the primary counter mode if high

		// Set the maximum and minimum limit values to watch
		pcnt_config.counter_h_lim = 32767;
		pcnt_config.counter_l_lim = -32768; 

		
		// Initialize PCNT unit
		pcnt_unit_config(&pcnt_config);
	}

	// Configure and enable the input filter
	pcnt_set_filter_value(self->pcntUnit, 1023);
	pcnt_filter_enable(self->pcntUnit);

	// Enable events on zero, maximum and minimum limit values
	pcnt_event_enable(self->pcntUnit, PCNT_EVT_ZERO);
	pcnt_event_enable(self->pcntUnit, PCNT_EVT_H_LIM);
	pcnt_event_enable(self->pcntUnit, PCNT_EVT_L_LIM);

	// Initialize PCNT's counter
	pcnt_counter_pause(self->pcntUnit);
	pcnt_counter_clear(self->pcntUnit);

	// Register ISR handler and enable interrupts for PCNT unit
	//pcnt_isr_register(pcnt_example_intr_handler, NULL, 0, &user_isr_handle);
	//pcnt_intr_enable(PCNT_TEST_UNIT);

	// Everything is set up, now go to counting
	pcnt_counter_resume(self->pcntUnit);

	//self->startingOffset = this->getAddition();

	return MP_OBJ_FROM_PTR(self);
}

STATIC void quadrature_encoder_print( const mp_print_t *print,
								  mp_obj_t self_in,
								  mp_print_kind_t kind ) {
	// get a ptr to the C-struct of the object
	quadrature_encoder_t *self = MP_OBJ_TO_PTR(self_in);
	// print the number
	printf ("Encoder (A=%u, B=%u)"
		, (uint8_t) self->gpioPinA
		, (uint8_t) self->gpioPinB);
}

STATIC mp_obj_t quadrature_value(mp_obj_t self_in) {
	quadrature_encoder_t *self = MP_OBJ_TO_PTR(self_in);

	int16_t value;
	pcnt_get_counter_value(self->pcntUnit, &value);

	return mp_obj_new_int(value);
}
MP_DEFINE_CONST_FUN_OBJ_1(quadrature_value_obj,
	quadrature_value);

static void quadrature_reset(mp_obj_t self_in) {
	quadrature_encoder_t *self = MP_OBJ_TO_PTR(self_in);
	pcnt_counter_clear(self->pcntUnit);
}
MP_DEFINE_CONST_FUN_OBJ_0(quadrature_reset_obj,
	quadrature_reset);

// creating the table of global members
STATIC const mp_rom_map_elem_t quadrature_encoder_locals_dict_table[] = {
	{
		MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&quadrature_value_obj)
		,MP_ROM_QSTR(MP_QSTR_reset), MP_ROM_PTR(&quadrature_reset_obj)
	}
};

STATIC MP_DEFINE_CONST_DICT(quadrature_encoder_locals_dict,
							quadrature_encoder_locals_dict_table);

// create the class-object itself
const mp_obj_type_t quadrature_type = {
	// "inherit" the type "type"
	{ &mp_type_type },
	 // give it a name
	.name = MP_QSTR_encoder,
	 // give it a print-function
	.print = quadrature_encoder_print,
	 // give it a constructor
	.make_new = quadrature_encoder_make_new,
	 // and the global members
	.locals_dict = (mp_obj_dict_t*)&quadrature_encoder_locals_dict,
};

// Define all properties of the example module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t quadrature_module_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_quadrature) },
	{ MP_ROM_QSTR(MP_QSTR_Encoder), MP_ROM_PTR(&quadrature_type) },
};
STATIC MP_DEFINE_CONST_DICT(quadrature_module_globals, quadrature_module_globals_table);

// Define module object.
const mp_obj_module_t quadrature_cmodule = {
	.base = { &mp_type_module },
	.globals = (mp_obj_dict_t*)&quadrature_module_globals,
};

// Register the module to make it available in Python
MP_REGISTER_MODULE(MP_QSTR_quadrature, quadrature_cmodule, MODULE_QUADRATURE_ENABLED);