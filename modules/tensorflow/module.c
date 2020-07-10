// Include required definitions first.
#include "py/obj.h"
#include "py/runtime.h"

#include "extern.h"

STATIC mp_obj_t tf_invoke(mp_obj_t mp_input)
{
	float input = mp_obj_get_float(mp_input);
	float result = testInvoke(input);
	return mp_obj_new_float(result);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(tf_invoke_obj, tf_invoke);




//------------------------------------
// python Model object

extern const mp_obj_type_t mp_model_type; 

// storage
typedef struct _model_t
{
	// base represents some basic information, like type
	mp_obj_base_t base;
	// a member created by us
	model_handle model;
} model_t;

//----------
mp_obj_t mp_model_make_new(const mp_obj_type_t * type,
	size_t n_args,
	size_t n_kw,
	const mp_obj_t * args)
{
	// check argument count
	mp_arg_check_num(n_args, n_kw, 0, 0, true);

	model_t * self = m_new_obj(model_t);
	self->base.type = &mp_model_type;
	self->model = create_model();
	return MP_OBJ_FROM_PTR(self);
}

//----------
STATIC void mp_model_print( const mp_print_t *print,
	mp_obj_t self_in,
	mp_print_kind_t kind )
{
	mp_print_str(print, "Tensorflow model");
}

//----------
STATIC mp_obj_t mp_model_get_input_size(mp_obj_t self_in)
{
	model_t *self = MP_OBJ_TO_PTR(self_in);
	size_t result = model_get_input_size(self->model);
	return mp_obj_new_int((int) result);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_model_get_input_size_obj,
	mp_model_get_input_size);

//----------
STATIC mp_obj_t mp_model_get_output_size(mp_obj_t self_in)
{
	model_t *self = MP_OBJ_TO_PTR(self_in);
	size_t result = model_get_output_size(self->model);
	return mp_obj_new_int((int) result);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_model_get_output_size_obj,
	mp_model_get_output_size);

//----------
STATIC mp_obj_t mp_model_invoke(mp_obj_t self_in, mp_obj_t input_obj)
{
	model_t *self = MP_OBJ_TO_PTR(self_in);

	size_t inputLength;
	mp_obj_t * inputItems;
	mp_obj_list_get(input_obj, &inputLength, &inputItems);
	float * inputTensorData = model_get_input(self->model);
	for(size_t i=0; i<inputLength; i++) {
		inputTensorData[i] = mp_obj_get_float(inputItems[i]);
	}

	// invoke
	if(!model_invoke(self->model)) {
		nlr_raise(mp_obj_new_exception_msg(&mp_type_Exception, MP_ERROR_TEXT("Model failed to invoke")));
	}

	// build output
	size_t outputLength = model_get_output_size(self->model);
	mp_obj_t outputItems[outputLength];
	float * outputTensorData = model_get_output(self->model);
	for(size_t i=0; i<outputLength; i++) {
		outputItems[i] = mp_obj_new_float(outputTensorData[i]);
	}

	return mp_obj_new_list(outputLength, outputItems);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_model_invoke_obj,
	mp_model_invoke);


// table of members for model class
STATIC const mp_rom_map_elem_t model_locals_dict_table[] = {
	{ MP_ROM_QSTR(MP_QSTR_invoke), MP_ROM_PTR(&mp_model_invoke_obj) }, 
	{ MP_ROM_QSTR(MP_QSTR_get_input_size), MP_ROM_PTR(&mp_model_get_input_size_obj) }, 
	{ MP_ROM_QSTR(MP_QSTR_get_output_size), MP_ROM_PTR(&mp_model_get_output_size_obj) }, 
};
STATIC MP_DEFINE_CONST_DICT(model_locals_dict,
							model_locals_dict_table);

// model class type
const mp_obj_type_t mp_model_type = {
	// "inherit" the type "type"
	{ &mp_type_type },
	 // give it a name
	.name = MP_QSTR_Model,
	 // give it a print-function
	.print = mp_model_print,
	 // give it a constructor
	.make_new = mp_model_make_new,
	 // and the global members
	.locals_dict = (mp_obj_dict_t*)&model_locals_dict,
};



// Module definition

STATIC const mp_rom_map_elem_t tensorflow_module_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR__name__), MP_ROM_QSTR(MP_QSTR_tensorflow)},
	{ MP_ROM_QSTR(MP_QSTR_testInvoke), MP_ROM_PTR(&tf_invoke_obj)},
	{ MP_ROM_QSTR(MP_QSTR_Model), MP_ROM_PTR(&mp_model_type)}
};
STATIC MP_DEFINE_CONST_DICT(tensorflow_module_globals, tensorflow_module_globals_table);

const mp_obj_module_t tf_user_cmodule = {
	.base = { &mp_type_module },
	.globals = (mp_obj_dict_t*)&tensorflow_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_tensorflow, tf_user_cmodule, MODULE_TENSORFLOW_ENABLED);
