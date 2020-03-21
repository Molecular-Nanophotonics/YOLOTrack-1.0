# YOLOv2 Training (Python)

*M. Fränzl*, Molecular Nanophtonics Group

## Discription

This repository contains Jupyter notebooks and Python modules for synthetic image generation, training and exporting YOLOv2 models with Python/Keras using the TensorFlow backend.

## Requirements 

- [Anaconda](https://www.anaconda.com/distribution/) for Python 3.x + TensorFlow 1.1x

## Repository Contents

- [ImageGenerator.ipynb](ImageGenerator.ipynb): A notebook that shows how to generate a synthetic image dataset for training. It depends on the `image_generator` and `xml_writer` modules. A sample output from the notebook is contained in the [images](images/) directory. 

- [Training.ipynb](Training.ipynb): The main notebook that implements and trains YOLOv2 in Keras using the TensorFlow backend. It depends on the `preprocessing` and `utils` modules. The notebook also shows how to export the trained model to the `model.pb` and `model.ini` files 

- [Inference.ipynb](Inference.ipynb): A notebook that shows how to import the `model.pb` and `model.ini` files and run a model inference.

