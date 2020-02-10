# YOLOv2 Framework for Digital Microscopy

*Martin Fränzl*, Molecular Nanophotonics Group

## Introduction 

This is a framework for the real-time localization and classification of objects in optical microscopy images using a single-shot covolutional neural network YOLO ("You Only Look Once") . We adapted the YOLOv2 architecture enabling to localize and classify objects at very low signal-to-noise ratios at 50 fps for images as large as 416 x 416 px.

The network is implemented in Python/Keras using the TensorFlow backend. For real-time inference the trained model is exported to a custom, C based dynamic link library (DLL). The DLL is based on the GPU supported [TensorFlow C API](https://www.tensorflow.org/install/lang_c) providing the fasted possible image processing and integrability in other programming languages such as LabVIEW, MATLAB and C++.

Here, we provide examples for the training in Python/Keras and for the model inference in LabVIEW and C++.

## Framework  Design

<p align="center"><img src="Resources/Software-Design.png" width=512></p>

## Training in Python/Keras

To generate synthetic images for training and validation the [Image_Generator.ipynb]("YOLOv2 Training (Python)/Image_Generator.ipynb") notebook can be used. By default these images are generated in the *images* folder. To train the model open the **Training+Export.ipynb** notebook to train the network. The notebook will export three files: `model_weights.h5`, `model.pb` and `model.ini`. 

The `model.pb` contains the graph stored as protocol buffer file format. The `model.ini` contains parameters required for decoding the output tensor, e.g., the number of grid cells, boxes etc. The `model.pb` and `model.ini` are required for deploying the model to LabVIEW, C++, ... 

The `model_weights.h5` file can be reloaded to the **Training+Export.ipynb**, e.g., for retraining the model.

 (Depending on the number of images and your hardware this might take a few hours).


## Inference in LabVIEW

