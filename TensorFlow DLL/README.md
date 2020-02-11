# TensorFlow DLL


**`int getVersion(char* tf_version)`**

**Description**<br>
This function returns the TensorFlow version. <br>

**Parameters**<br>
tf_version (char*): Pointer to a array of characters allocated by the user
    
**Return** <br>
int: 1  No Error. <br>
     0  Error.


```c
int getVersion(char* tf_version);
    /* 
    Description:    This function returns the TensorFlow version. 

    Parameters:     tf_version (char*): Pointer to a array of characters allocated by the user.

    Return:         int: 
                    1  No Error. 
                    0  Error.
    */
```

```c
int getGPUs(int* num_gpus);
    /*
    Description:
    This function returns the number of available GPUs. 

    Parameters:
    num_gpus (int*): Number of available GPUs.

    Return:
    int: 1  No Error.
         0  Error.
   */
```

``
`int setupTF(char* file, int64_t* in_shape, int in_dim, char* in_name, int64_t* out_shape, int out_dim, char* out_name);`
`int runTF(float* input_tensor, float* output_tensor);`

