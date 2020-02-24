# YOLOv2 Framework for Digital Microscopy

*Martin Fränzl*, Molecular Nanophotonics Group

## Contents

- [Discription](#discription)
- [Repository Contents](#repository-contents)

## Discription 

This is a framework for the real-time localization and classification of objects in optical microscopy images using a single-shot covolutional neural network YOLO ("You Only Look Once") . We adapted the YOLOv2 architecture enabling to localize and classify objects at very low signal-to-noise ratios at 50 fps for images as large as 416 x 416 px.

The network is implemented in Python/Keras using the TensorFlow backend. For real-time inference the trained model is exported to a custom, C based dynamic link library (TF.dll). The DLL is based on the GPU supported [TensorFlow C API](https://www.tensorflow.org/install/lang_c) providing the fastest possible image processing and is readily integrable in other programming languages such as LabVIEW and C++.

Here, we provide examples for the training in Python/Keras and for the model inference in LabVIEW and C++.

## Repository Contents

- [TF DLL](./TF%20DLL): ...
- [YOLOv2 DLL](./YOLOv2%20DLL): ...
- [YOLOv2 Inference (C++)](./YOLOv2%20Inference%20(C%2B%2B)): ...
- [YOLOv2 Inference (LabVIEW)](./YOLOv2%20Inference%20(LabVIEW)): ...
- [YOLOv2 Training (Python/Keras)](./YOLOv2%20Training%20(Python/Keras)): ...

<p align="center"><img src="Resources/Software-Design.png" width=550></p>

The `TF.dll` is a library for TensorFlow model inference that can be used with any TensorFlow model. It is a copy of [TensorFlow-Framework/TF DLL](https://github.com/Molecular-Nanophotonics/TensorFlow-Framework). The `YOLOv2.dll` adds specific functions required for YOLO, e.g., the decoding of the output tensor.

## Training in Python/Keras

To generate synthetic images for training and validation the [Image_Generator.ipynb](https://github.com/Molecular-Nanophotonics/YOLOv2-Framework/tree/master/YOLOv2%20Training%20(Python)/Image_Generator.ipynb) notebook can be used. By default these images are generated in the *images* folder. To train the model open the **Training+Export.ipynb** notebook to train the network. The notebook will export three files: `model_weights.h5`, `model.pb` and `model.ini`. 

The `model.pb` contains the graph stored as protocol buffer file format. The `model.ini` contains parameters required for decoding the output tensor, e.g., the number of grid cells, boxes etc. The `model.pb` and `model.ini` are required for deploying the model to LabVIEW, C++, ... 

The `model_weights.h5` file can be reloaded to the **Training+Export.ipynb**, e.g., for retraining the model.

 (Depending on the number of images and your hardware this might take a few hours).

## Inference in LabVIEW

