
extern "C" __declspec(dllexport) int getVersion(char* tf_version);
extern "C" __declspec(dllexport) int getGPUs(int* gpu_out);
extern "C" __declspec(dllexport) int setupTF(char* file, int64_t* in_shape, int in_dim, char* in_name, int64_t* out_shape, int out_dim, char* out_name);
extern "C" __declspec(dllexport) int runTF(float* input_tensor, float* output_tensor);