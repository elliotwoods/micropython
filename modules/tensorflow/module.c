// Include required definitions first.
#include "py/obj.h"
#include "py/runtime.h"

#include "extern.h"

STATIC mp_obj_t tf_invoke(mp_obj_t mp_input) {
	float input = mp_obj_get_float(mp_input);
	float result = testInvoke(input);
	return mp_obj_new_float(result);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(tf_invoke_obj, tf_invoke);

STATIC const mp_rom_map_elem_t tf_module_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR__name__), MP_ROM_QSTR(MP_QSTR_tensorflow)},
	{ MP_ROM_QSTR(MP_QSTR_invoke), MP_ROM_PTR(&tf_invoke_obj)}
};
STATIC MP_DEFINE_CONST_DICT(tf_module_globals, tf_module_globals_table);

const mp_obj_module_t tf_user_cmodule = {
	.base = { &mp_type_module },
	.globals = (mp_obj_dict_t*)&tf_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_tensorflow, tf_user_cmodule, 1);