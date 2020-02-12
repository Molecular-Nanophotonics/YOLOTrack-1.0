# TensorFlow DLL

```c
int getVersion(char* tf_version)
/*
    Description:    This function returns the TensorFlow version. 

    Parameters:     tf_version (char*): Pointer to a character arry to store the TensorFlow version allocated by the user.

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
    Description:    This function sets up the TensorFlow session, e.g., load the model graph and allocate the required memory. 

    Parameters:     file (char*): Path to the model graph saved as protocol buffer file
                    in_shape (int64_t*): Shape of the input tensor.
                    in_dim (int): Dimension of the input tensor.
                    in_name (char*): Name of the input node.
                    out_shape (int64_t*): Shape of the output tensor.
                    out_dim (int): Dimension of the output tensor.
                    out_name (char*): Name of the output node.

    Return:         int:
                    1  No Error.
                    0  Error.
*/
```

```c
int runTF(float* input_tensor, float* output_tensor);
/*
    Description:    This functions runs the model for a given input tensor and returns the output tensor.

    Parameters:     input_tensor (float*): Input tensor.
                    output_tensor (float*): Output tensor.
                    
    Return:         int:
                    1  No Error.
                    0  Error.
*/
```
