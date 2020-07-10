#include "Model.h"
#include "sine_model.h"

tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;

tflite::AllOpsResolver resolver;

//----------
Model::Model(size_t tensorArenaSize)
: tensorArenaSize(tensorArenaSize)
{
	this->tensorArena = new uint8_t[tensorArenaSize];
}

//----------
Model::~Model()
{
	this->unload();

	delete[] this->tensorArena;
}

//----------
void
Model::load(unsigned char * data, size_t length)
{
	this->unload();

	this->model = ::tflite::GetModel(g_model);
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
	
	this->interpreter->AllocateTensors();
}

//---------
void
Model::unload()
{
	if(this->model) {
		delete this->model;
		this->model = nullptr;
	}

	if(this->interpreter) {
		delete this->interpreter;
		this->interpreter = nullptr;
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