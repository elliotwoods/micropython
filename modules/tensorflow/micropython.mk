TENSORFLOW_MOD_DIR := ../../../modules/tensorflow

# Add all C files to SRC_USERMOD.
SRC_USERMOD_CPP += $(TENSORFLOW_MOD_DIR)/tensorflow.cpp

# We can add our module folder to include paths if needed
# This is not actually needed in this example.
CFLAGS_USERMOD += -I$(TENSORFLOW_MOD_DIR)

# include tensorflow path
CFLAGS_USERMOD += -I../../../tensorflow
CFLAGS_USERMOD += -I../../../tensorflow/tensorflow/lite/micro/tools/make/downloads/flatbuffers/include