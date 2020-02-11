# TensorFlow DLL

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
