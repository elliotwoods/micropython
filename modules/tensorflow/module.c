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
	model_ptr model;
	unsigned char* heap_area;
} model_t;

//----------
mp_obj_t mp_model_make_new(const mp_obj_type_t * type,
	size_t n_args,
	size_t n_kw,
	const mp_obj_t * args)
{
	// check argument count
	mp_arg_check_num(n_args, n_kw, 0, 1, true);

	model_t * self = m_new_obj(model_t);
	self->base.type = &mp_model_type;

	if (n_args == 0) {
		self->model = create_model();
	}
	else {
		size_t heapAreaSize = mp_obj_get_int(args[0]);
		self->model = create_model_with_heap_size(heapAreaSize);
	}
	self->heap_area = model_get_heap_area(self->model);
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
STATIC mp_obj_t mp_model_load(mp_obj_t self_in, mp_obj_t data_in)
{
	model_t *self = MP_OBJ_TO_PTR(self_in);

	size_t dataLength;
	const char * data = mp_obj_str_get_data(data_in, &dataLength);

	model_load(self->model, data, dataLength);

	return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_model_load_obj,
	mp_model_load);

//----------
STATIC mp_obj_t mp_model_unload(mp_obj_t self_in)
{
	model_t *self = MP_OBJ_TO_PTR(self_in);

	model_unload(self->model);

	return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_model_unload_obj,
	mp_model_unload);

//----------
STATIC mp_obj_t mp_model_get_input_size(mp_obj_t self_in)
{
	model_t *self = MP_OBJ_TO_PTR(self_in);

	if(!model_is_loaded(self->model)) {
		nlr_raise(mp_obj_new_exception_msg(&mp_type_Exception, MP_ERROR_TEXT("Model is not loaded")));
	}

	size_t result = model_get_input_size(self->model);
	return mp_obj_new_int((int) result);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_model_get_input_size_obj,
	mp_model_get_input_size);

//----------
STATIC mp_obj_t mp_model_get_output_size(mp_obj_t self_in)
{
	model_t *self = MP_OBJ_TO_PTR(self_in);

	if(!model_is_loaded(self->model)) {
		nlr_raise(mp_obj_new_exception_msg(&mp_type_Exception, MP_ERROR_TEXT("Model is not loaded")));
	}

	size_t result = model_get_output_size(self->model);
	return mp_obj_new_int((int) result);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_model_get_output_size_obj,
	mp_model_get_output_size);

//----------
STATIC mp_obj_t mp_model_invoke(mp_obj_t self_in, mp_obj_t input_obj)
{
	model_t *self = MP_OBJ_TO_PTR(self_in);

	// check model is loaded
	if(!model_is_loaded(self->model)) {
		nlr_raise(mp_obj_new_exception_msg(&mp_type_Exception, MP_ERROR_TEXT("Model is not loaded")));
	}

	// check input type
	if(mp_obj_get_type(input_obj) != &mp_type_list) {
		nlr_raise(mp_obj_new_exception_msg(&mp_type_ValueError, MP_ERROR_TEXT("Input must be a list")));
	}

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
	mp_obj_t* outputItems = m_new(mp_obj_t, outputLength);
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
	{ MP_ROM_QSTR(MP_QSTR_load), MP_ROM_PTR(&mp_model_load_obj) }, 
	{ MP_ROM_QSTR(MP_QSTR_unload), MP_ROM_PTR(&mp_model_unload_obj) }, 
	
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


//----------
STATIC mp_obj_t mp_get_sine_model()
{
	size_t dataLength;
	const char * data = get_sine_model(&dataLength);
	return mp_obj_new_str(data, dataLength);
}
MP_DEFINE_CONST_FUN_OBJ_0(mp_get_sine_model_obj,
	mp_get_sine_model);


// Module definition

STATIC const mp_rom_map_elem_t tensorflow_module_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR__name__), MP_ROM_QSTR(MP_QSTR_tensorflow)},
	{ MP_ROM_QSTR(MP_QSTR_test_invoke), MP_ROM_PTR(&tf_invoke_obj)},
	{ MP_ROM_QSTR(MP_QSTR_get_sine_model), MP_ROM_PTR(&mp_get_sine_model_obj)},
	{ MP_ROM_QSTR(MP_QSTR_Model), MP_ROM_PTR(&mp_model_type)}
};
STATIC MP_DEFINE_CONST_DICT(tensorflow_module_globals, tensorflow_module_globals_table);

const mp_obj_module_t tf_user_cmodule = {
	.base = { &mp_type_module },
	.globals = (mp_obj_dict_t*)&tensorflow_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_tensorflow, tf_user_cmodule, MODULE_TENSORFLOW_ENABLED);
