USERMODULES_DIR := $(USERMOD_DIR)
#USERMODULES_DIR := ../../../modules/tensorflow

# Add all C files to SRC_USERMOD.
SRC_USERMOD += $(USERMODULES_DIR)/module.c

SRC_USERMOD_CPP += $(USERMODULES_DIR)/Model.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/sine_model.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/extern.cpp

#tensorflow lite micro
SRC_USERMOD += $(USERMODULES_DIR)/tensorflow/lite/c/common.c
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/core/api/error_reporter.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/core/api/flatbuffer_conversions.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/core/api/op_resolver.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/core/api/tensor_utils.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/kernels/internal/quantization_util.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/kernels/kernel_util.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/all_ops_resolver.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/benchmarks/keyword_scrambled_model_data.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/debug_log.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/activations.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/add.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/arg_min_max.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/ceil.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/circular_buffer.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/comparisons.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/concatenation.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/conv.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/depthwise_conv.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/dequantize.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/elementwise.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/ethosu.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/floor.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/fully_connected.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/hard_swish.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/l2norm.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/logical.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/logistic.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/maximum_minimum.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/mul.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/neg.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/pack.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/pad.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/pooling.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/prelu.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/quantize.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/reduce.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/reshape.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/resize_nearest_neighbor.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/round.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/softmax.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/split.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/strided_slice.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/sub.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/svdf.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/tanh.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/kernels/unpack.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/memory_helpers.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/memory_planner/greedy_memory_planner.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/memory_planner/linear_memory_planner.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/micro_allocator.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/micro_error_reporter.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/micro_interpreter.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/micro_optional_debug_tools.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/micro_profiler.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/micro_string.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/micro_time.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/micro_utils.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/recording_micro_allocator.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/recording_simple_memory_allocator.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/simple_memory_allocator.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/testing/test_conv_model.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/testing/test_utils.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/tensorflow/lite/micro/test_helpers.cpp

#ruy
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/allocator.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/allocator_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/apply_multiplier.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/benchmark.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/blocking_counter.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/block_map.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/block_map_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/check_macros_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/context.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/context_get_ctx.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/context_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/cpuinfo.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/create_trmul_params.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/ctx.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/ctx_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/example.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/matrix_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/mul_params_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/pmu.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/prepacked_cache.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/prepacked_cache_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/prepare_packed_matrices.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/profiler/instrumentation.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/profiler/profiler.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/profiler/test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/profiler/test_instrumented_library.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/profiler/treeview.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/size_util_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/system_aligned_alloc.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/test_fast.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/test_slow.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/test_special_mul_params.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/thread_pool.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/trmul.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/tune.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/tune_test.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/tune_tool.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/wait.cpp
#SRC_USERMOD_CPP += $(USERMODULES_DIR)/ruy/wait_test.cpp

# We can add our module folder to include paths if needed
# This is not actually needed in this example.
CFLAGS_USERMOD += -I$(USERMODULES_DIR)

# include tensorflow paths
CFLAGS_USERMOD += -I$(USERMODULES_DIR)/gemmlowp/
CFLAGS_USERMOD += -I$(USERMODULES_DIR)/ruy/

# include tensorflow path
#CFLAGS_USERMOD += -I../../../tensorflow
#CFLAGS_USERMOD += -I../../../tensorflow/tensorflow/lite/micro/tools/make/downloads/flatbuffers/include
#CFLAGS_USERMOD += -I../../../tensorflow/tensorflow/lite/micro/tools/make/gen/esp_xtensa-esp32/prj/hello_world/esp-idf/components/tfmicro/
#CFLAGS_USERMOD += -I../../../tensorflow/tensorflow/lite/micro/tools/make/downloads/flatbuffers/include

CFLAGS_USERMOD += -Iboards/GENERIC
