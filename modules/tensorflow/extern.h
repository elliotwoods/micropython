#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#include <stddef.h>

EXTERNC float testInvoke(float);

typedef void * model_ptr;

EXTERNC model_ptr create_model();
EXTERNC model_ptr create_model_with_heap_size(size_t heapSize);

EXTERNC void delete_model(model_ptr);

EXTERNC void model_load(model_ptr, const char *, size_t);
EXTERNC void model_unload(model_ptr);
EXTERNC bool model_is_loaded(model_ptr);
EXTERNC void * model_get_heap_area(model_ptr);
EXTERNC float * model_get_input(model_ptr);
EXTERNC float * model_get_output(model_ptr);

EXTERNC size_t model_get_input_size(model_ptr);
EXTERNC size_t model_get_output_size(model_ptr);
EXTERNC bool model_check_size(model_ptr, size_t inputSize, size_t outputSize);

EXTERNC bool model_invoke(model_ptr);

EXTERNC const char * get_sine_model(size_t * length);