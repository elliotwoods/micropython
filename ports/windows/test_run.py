import gc
import tensorflow

model = tensorflow.Model();
model.load(tensorflow.get_sine_model())

for i in range(100):
	for j in range(100):
		model.invoke([0.])
	print(i)
	gc.collect()