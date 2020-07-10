#include "extern.h"
#include "Model.h"

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
	newModel->load(nullptr, 0);

	auto nextIndex = models.size();
	models.push_back(newModel);
	return nextIndex;
}

void delete_model(model_handle model) {
	delete models[model];
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