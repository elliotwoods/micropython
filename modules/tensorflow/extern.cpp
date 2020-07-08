#include "extern.h"
#include "Model.h"

Model* model = 0;

float testInvoke(float input) {
	if(!model) {
		model = new Model();
		model->load(nullptr, 0);
	}

	return model->invoke(input);
}
