#include "Model.h"
#include "sine_model.h"

#include <cstdlib>

tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;

tflite::AllOpsResolver resolver;

const size_t alignment = 16;
uint8_t heapAreaGlobal[2 * 1024 + alignment];

//----------
Model::Model(size_t tensorArenaSize)
{
	this->heapArea = malloc(tensorArenaSize + alignment);
	{
		auto tensorAreaAligned = ((uintptr_t)this->heapArea) + alignment;
		tensorAreaAligned -= tensorAreaAligned % alignment;
		this->tensorArena = (uint8_t*)tensorAreaAligned;
	}

	this->tensorArenaSize = tensorArenaSize;
}

//----------
Model::~Model()
{
	this->unload();

	//free(this->heapArea);
}

//----------
void
Model::load(const char * data, size_t length)
{
	this->unload();

	this->modelString.assign(data, length);
	this->model = ::tflite::GetModel(this->modelString.c_str());
	if (this->model->version() != TFLITE_SCHEMA_VERSION) {
	TF_LITE_REPORT_ERROR(error_reporter,
		"Model provided is schema version %d not equal "
		"to supported version %d.\n",
		this->model->version(), TFLITE_SCHEMA_VERSION);
	}

	this->interpreter = new tflite::MicroInterpreter(model
		, resolver
		, this->tensorArena
		, this->tensorArenaSize
		, error_reporter);
	
	if(this->interpreter->AllocateTensors() != kTfLiteOk) {
		TF_LITE_REPORT_ERROR(error_reporter,
			"Cannot allocate tensors");
	}
}

//---------
void
Model::unload()
{
	if(this->interpreter) {
		delete this->interpreter;
		this->interpreter = nullptr;
	}

	if(this->model) {
		this->modelString.clear();
		this->model = nullptr;
	}
}

//----------
bool
Model::isLoaded() const
{
	if(this->model && this->interpreter) {
		return true;
	}
	else {
		return false;
	}
}

//----------
void *
Model::getHeapArea() const
{
	return this->heapArea;
}

//----------
float *
Model::getInput()
{
	return this->interpreter->input(0)->data.f;
}

//----------
float *
Model::getOutput()
{
	return this->interpreter->output(0)->data.f;
}

//----------
size_t
Model::getInputSize() const
{
	auto & dims = this->interpreter->input(0)->dims;
	return dims->data[0] * dims->data[1];
}

//----------
size_t
Model::getOutputSize() const
{
	auto & dims = this->interpreter->output(0)->dims;
	return dims->data[0] * dims->data[1];
}

//----------
bool
Model::checkSize(size_t inputSize, size_t outputSize) const
{
	if(!this->isLoaded()) {
		return false;
	}

	// check the input format is correct
	{
		auto input = this->interpreter->input(0);

		if(!input) {
			return false;
		}

		// 2D 
		if(input->dims->size != 2) {
			return false;
		}

		// size
		if((size_t) (input->dims->data[0] * input->dims->data[1]) != inputSize) {
			return false;
		}

		// float type
		if(input->type != kTfLiteFloat32) {
			return false;
		}
	}

	// check output format
	{
		auto output = interpreter->output(0);

		if(!output) {
			return false;
		}

		// 2D 
		if(output->dims->size != 2) {
			return false;
		}

		// 1x1 size
		if( (size_t) (output->dims->data[0] * output->dims->data[1]) != outputSize) {
			return false;
		}

		// float type
		if(output->type != kTfLiteFloat32) {
			return false;
		}
	}

	return true;
}

//----------
bool
Model::invoke()
{
	// run the model
	auto status = this->interpreter->Invoke();
	if(status != kTfLiteOk) {
		return false;
	}

	return true;
}