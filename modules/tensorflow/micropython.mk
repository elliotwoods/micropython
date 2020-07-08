USERMODULES_DIR := $(USERMOD_DIR)
#USERMODULES_DIR := ../../../modules/tensorflow

# Add all C files to SRC_USERMOD.
SRC_USERMOD += $(USERMODULES_DIR)/module.c
SRC_USERMOD_CPP += $(USERMODULES_DIR)/Model.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/sine_model.cpp
SRC_USERMOD_CPP += $(USERMODULES_DIR)/extern.cpp

# We can add our module folder to include paths if needed
# This is not actually needed in this example.
CFLAGS_USERMOD += -I$(USERMODULES_DIR)

# include tensorflow path
CFLAGS_USERMOD += -I../../../tensorflow
CFLAGS_USERMOD += -I../../../tensorflow/tensorflow/lite/micro/tools/make/downloads/flatbuffers/include
CFLAGS_USERMOD += -I../../../tensorflow/tensorflow/lite/micro/tools/make/gen/esp_xtensa-esp32/prj/hello_world/esp-idf/components/tfmicro/
CFLAGS_USERMOD += -I../../../tensorflow/tensorflow/lite/micro/tools/make/downloads/flatbuffers/include
CFLAGS_USERMOD += -Iboards/GENERIC
