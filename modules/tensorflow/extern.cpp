#include "extern.h"
#include "Model.h"
#include "sine_model.h"

#include <vector>

std::vector<Model*> models;

Model * testModel;

float testInvoke(float input) {
	if(!testModel) {
		testModel = new Model();
		testModel->load(nullptr, 0);
	}

	testModel->checkSize(1, 1);
	testModel->getInput()[0] = input;
	testModel->invoke();
	return testModel->getOutput()[0];
}

model_handle create_model() {
	auto newModel = new Model;

	auto nextIndex = models.size();
	models.push_back(newModel);
	return nextIndex;
}

void delete_model(model_handle model) {
	delete models[model];
}

void model_load(model_handle model, const char * data, size_t length) {
	models[model]->load(data, length);
}

void model_unload(model_handle model) {
	models[model]->unload();
}

bool model_is_loaded(model_handle model) {
	return models[model]->isLoaded();
}

float * model_get_input(model_handle model) {
	return models[model]->getInput();
}

float * model_get_output(model_handle model) {
	return models[model]->getOutput();
}

bool model_check_size(model_handle model, size_t inputSize, size_t outputSize) {
	return models[model]->checkSize(inputSize, outputSize);
}

bool model_invoke(model_handle model) {
	return models[model]->invoke();
}

size_t model_get_input_size(model_handle model) {
	return models[model]->getInputSize();
}

size_t model_get_output_size(model_handle model) {
	return models[model]->getOutputSize();
}

const char * get_sine_model(size_t * length) {
	* length = (size_t) g_model_len;
	return (const char *) g_model;
}