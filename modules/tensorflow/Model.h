
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

class Model {
public:
	Model(size_t tensorArenaSize = 2 * 1024);
	~Model();

	void load(unsigned char * data, size_t length);
	void unload();
	
	bool isLoaded() const;

	float invoke(float);
protected:
	size_t tensorArenaSize;
	uint8_t * tensorArena;

	const tflite::Model* model = nullptr;
	tflite::MicroInterpreter * interpreter = nullptr;
};