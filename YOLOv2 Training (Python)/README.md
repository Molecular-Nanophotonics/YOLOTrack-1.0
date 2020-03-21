# YOLOv2 Training (Python)

*M. Fränzl*, Molecular Nanophtonics Group

## Discription

This repository contains Jupyter notebooks and Python modules for synthetic image generation, training and exporting YOLOv2 models with Python/Keras using the TensorFlow backend.

## Requirements 

- [Anaconda](https://www.anaconda.com/distribution/) for Python 3.x + TensorFlow 1.1x

## Repository Contents

- [ImageGenerator.ipynb](ImageGenerator.ipynb): Notebook that shows how to generate a synthetic image dataset for training. It depends on **image_generator** and **xml_writer**. The **image_generator** module implements the synthetic image generation whereas the **xml_writer** provides function to save annotations the Pascal VOC format. A sample dataset generated with the notebook this notebook is contained in the **images** directory. 

- [Training.ipynb](Training.ipynb): Notebook that implements YOLOv2 in Keras and demonstrates how to train the model and how to freeze and export the trained model. It depends on **pre_processing** and **utils**. The **pre_processing** module comprises functions to parse the annotations and implements the *BatchGenerator* required for training. The **utils** module provides functions for the output decoding as well as for the model export.

- [Inference.ipynb](Inference.ipynb): Notebook that shows how to load the exported `model.pb` and `model.ini` files and run a model inference. It requires the **utils** module for the output decoding.

