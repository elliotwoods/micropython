#include "Model.h"
#include "sine_model.h"

tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;

tflite::AllOpsResolver resolver;

//----------
Model::Model(size_t tensorArenaSize)
: tensorArenaSize(tensorArenaSize) {
	this->tensorArena = new uint8_t[tensorArenaSize];
}

//----------
Model::~Model() {
	this->unload();

	delete[] this->tensorArena;
}

//----------
void Model::load(unsigned char * data, size_t length) {
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
void Model::unload() {
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
bool Model::isLoaded() const {
	if(this->model && this->interpreter) {
		return true;
	}
	else {
		return false;
	}
}

//----------
float Model::invoke(float inputValue) {
	float error = -10.0f;

	if(!this->isLoaded()) {
		return error;
	}

	auto input = this->interpreter->input(0);

	// check the input format is correct
	{
		if(!input) {
			return error;
		}

		// 2D 
		if(input->dims->size != 2) {
			return error;
		}

		// 1x1 size
		if(input->dims->data[0] != 1) {
			return error;
		}
		if(input->dims->data[1] != 1) {
			return error;
		}

		// float type
		if(input->type != kTfLiteFloat32) {
			return error;
		}
	}

	input->data.f[0] = inputValue;

	// run the model
	auto status = this->interpreter->Invoke();
	if(status != kTfLiteOk) {
		return error;
	}

	auto output = interpreter->output(0);

	// check output format
	{
		if(!output) {
			return error;
		}

		// 2D 
		if(output->dims->size != 2) {
			return error;
		}

		// 1x1 size
		if(output->dims->data[0] != 1) {
			return error;
		}
		if(output->dims->data[1] != 1) {
			return error;
		}

		// float type
		if(output->type != kTfLiteFloat32) {
			return error;
		}
	}

	auto value = output->data.f[0];
	return value;
}