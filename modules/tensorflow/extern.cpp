#include "extern.h"
#include "Model.h"
#include "sine_model.h"

extern "C" {
	#include "py/obj.h"
	#include "py/runtime.h"
}


#include <vector>

#include <stdarg.h>
int mp_vprintf(const mp_print_t* print, const char* fmt, va_list args);
int DEBUG_printf(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	int ret = mp_vprintf(MICROPY_DEBUG_PRINTER, fmt, ap);
	va_end(ap);
	return ret;
}

Model * testModel;

float testInvoke(float input) {
	if(!testModel) {
		testModel = new Model();
		size_t length;
		auto sineModel = get_sine_model(&length);
		testModel->load(sineModel, length);
	}

	testModel->checkSize(1, 1);
	testModel->getInput()[0] = input;
	testModel->invoke();
	return testModel->getOutput()[0];
}

const char * get_sine_model(size_t * length) {
	* length = (size_t) g_model_len;
	return (const char *) g_model;
}

// Model :

model_ptr create_model() {
	return new Model();
}

model_ptr create_model_with_heap_size(size_t heapSize) {
	return new Model(heapSize);
}

void delete_model(model_ptr model) {
	delete model;
}

void model_load(model_ptr model, const char * data, size_t length) {
	((Model*)model)->load(data, length);
}

void model_unload(model_ptr model) {
	((Model*)model)->unload();
}

bool model_is_loaded(model_ptr model) {
	return ((Model*)model)->isLoaded();
}

void * model_get_heap_area(model_ptr model) {
	return ((Model*)model)->getHeapArea();
}

float * model_get_input(model_ptr model) {
	return ((Model*)model)->getInput();
}

float * model_get_output(model_ptr model) {
	return ((Model*)model)->getOutput();
}

bool model_check_size(model_ptr model, size_t inputSize, size_t outputSize) {
	return ((Model*)model)->checkSize(inputSize, outputSize);
}

bool model_invoke(model_ptr model) {
	try {
		return ((Model*)model)->invoke();
	}
	catch (...) {
		nlr_raise(mp_obj_new_exception_msg(&mp_type_Exception, MP_ERROR_TEXT("Exception occured in tensorflow")));
	}
}

size_t model_get_input_size(model_ptr model) {
	return ((Model*)model)->getInputSize();
}

size_t model_get_output_size(model_ptr model) {
	return ((Model*)model)->getOutputSize();
}