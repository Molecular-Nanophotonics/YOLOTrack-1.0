# TF DLL 

*M. Fränzl*, Molecular Nanophtonics Group

## Discription

`TF.dll` is a dynamic link library for model inference build on top of the GPU supported [TensorFlow C API](https://www.tensorflow.org/install/lang_c). 

## Requirements

- Visual Studio 2015
- [CUDA Toolkit 10.0](https://developer.nvidia.com/cuda-10.0-download-archive) with Visual Studion Integration installed
- [CUDNN v7.6.4](https://developer.nvidia.com/rdp/cudnn-archive)
- [TensorFlow C API](https://www.tensorflow.org/install/lang_c) (1.13.1, GPU)


## Users Guide

The DLL is defined in [TF.h](TF.h) and designed for ...



```c
int getVersion(char* tf_version)
/*
    Description:    This function returns the TensorFlow version. 

    Parameters:     tf_version (char*): Pointer to a array of characters allocated by the user.

    Return:         int 
                    1  No Error. 
                    0  Error.
*/                
```

```c
int getGPUs(int* num_gpus)
/*
    Description:    This function returns the number of available GPUs. 

    Parameters:     num_gpus (int*): Number of available GPUs.

    Return:         int:
                    1  No Error.
                    0  Error.
*/
```

```c
int setupTF(char* file, int64_t* in_shape, int in_dim, char* in_name, int64_t* out_shape, int out_dim, char* out_name)
/*
    Description:    This function sets up the TensorFlow session. 

    Parameters:     file (char*): ...

    Return:         int:
                    1  No Error.
                    0  Error.
*/
```

```c
int runTF(float* input_tensor, float* output_tensor);
/*
    Description:    ... 

    Parameters:     input_tensor (float*): ...

    Return:         int:
                    1  No Error.
                    0  Error.
*/
```

``
``

