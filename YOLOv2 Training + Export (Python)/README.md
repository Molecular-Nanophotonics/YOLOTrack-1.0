# Training in Python Keras with TensorFlow Backend

The workflow is as follows:
1. Generate images for training and validation using the **Image_Generator.ipynb** notebook. By default these images are generated in the *images* folder.
2. Run the **Training+Export.ipynb** notebook to train the network. The notebook exports three files: `model_weights.h5`, `model.pb`, `model.ini`. 
3. The `model.pb` and `model.ini` files are required for deploying the model to different applications (LabVIEW, C++, ...). The `model_weights.h5` can be reloaded to the **Training+Export.ipynb** for retraining the model.


The `model.pb` contains the graph stored as protocol buffer file format. The `model.ini` contains parameters required for decoding the output tensor, e.g., the number of grid cells, boxes etc. The `model.pb` and `model.ini` are required for deploying the model to LabVIEW. 

 (Depending on the number of images and your hardware this might take a few hours).
