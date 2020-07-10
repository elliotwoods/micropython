
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

class Model {
public:
	Model(size_t tensorArenaSize = 2 * 1024);
	~Model();

	void load(const char * data, size_t length);
	void unload();
	
	bool isLoaded() const;

	float * getInput();
	float * getOutput();

	size_t getInputSize() const;
	size_t getOutputSize() const;
	bool checkSize(size_t inputSize, size_t outputSize) const;

	bool invoke();

protected:
	size_t tensorArenaSize;
	uint8_t * tensorArena;

	const tflite::Model* model = nullptr;
	tflite::MicroInterpreter * interpreter = nullptr;
};