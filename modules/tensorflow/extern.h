#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#include <stddef.h>

EXTERNC float testInvoke(float);

typedef size_t model_handle;


EXTERNC model_handle create_model();
EXTERNC void delete_model(model_handle);

EXTERNC void model_load(model_handle, const char *, size_t);
EXTERNC void model_unload(model_handle);
EXTERNC bool model_is_loaded(model_handle);
EXTERNC float * model_get_input(model_handle);
EXTERNC float * model_get_output(model_handle);

EXTERNC size_t model_get_input_size(model_handle);
EXTERNC size_t model_get_output_size(model_handle);
EXTERNC bool model_check_size(model_handle, size_t inputSize, size_t outputSize);

EXTERNC bool model_invoke(model_handle);

EXTERNC const char * get_sine_model(size_t * length);