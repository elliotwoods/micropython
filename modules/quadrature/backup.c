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

#include "Encoder.h"

// this is the actual C-structure for our new object
typedef struct _quadrature_encoder_t {
	// base represents some basic information, like type
	mp_obj_base_t base;

	Encoder encoder;
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
	self->encoder = encoder_make((gpio_num_t) pin_A
		, (gpio_num_t)pin_B);

	return MP_OBJ_FROM_PTR(self);
}

STATIC void quadrature_encoder_print( const mp_print_t *print,
								  mp_obj_t self_in,
								  mp_print_kind_t kind ) {
	// get a ptr to the C-struct of the object
	quadrature_encoder_t *self = MP_OBJ_TO_PTR(self_in);
	// print the number
	printf ("Encoder (A=%u, B=%u)"
		, (uint8_t) self->encoder.gpioPinA
		, (uint8_t) self->encoder.gpioPinB);
}

STATIC mp_obj_t quadrature_value(mp_obj_t self_in) {
	quadrature_encoder_t *self = MP_OBJ_TO_PTR(self_in);
	return mp_obj_new_int(encoder_get_value(& self->encoder));
}
MP_DEFINE_CONST_FUN_OBJ_1(quadrature_value_obj,
	quadrature_value);

// creating the table of global members
STATIC const mp_rom_map_elem_t quadrature_encoder_locals_dict_table[] = {
	{ MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&quadrature_value_obj) }
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