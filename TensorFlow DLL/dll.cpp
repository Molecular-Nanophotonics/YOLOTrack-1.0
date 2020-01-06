#include "tensorflow/c/c_api.h"

#include <windows.h>
#include <vector>

int IMAGE_W = 416;
int IMAGE_H = 416;
int GRID_W = 13;
int GRID_H = 13;
int BOXES = 5;
int CLASSES = 3;
float* ANCHORS;
int N_MAX;

TF_Status* status;
TF_Graph* graph;
TF_Buffer* graph_def;
TF_ImportGraphDefOptions* graph_opts;
TF_SessionOptions* sess_opts;
TF_Session* session;

float* values;
int input_dim;
int64_t* input_shape;
int input_size;
std::vector<TF_Output> inputs;
std::vector<TF_Tensor*> input_values;

int output_dim;
int64_t* output_shape;
int output_size;
std::vector<TF_Output> outputs;
std::vector<TF_Tensor*> output_values;

float* _x;
float* _y;
float* _w;
float* _h;
int* _c;
float* _score;
int* idx_list;

extern "C" __declspec(dllexport) int getVersion(char* tf_version);
extern "C" __declspec(dllexport) int setupTF(char* file, int64_t* in_shape, int in_dim, char* in_name, int64_t* out_shape, int out_dim, char* out_name);
extern "C" __declspec(dllexport) int runTF(float* input_tensor, float* output_tensor);
extern "C" __declspec(dllexport) int setupDecodeYOLO(int image_w, int image_h, int grid_w, int grid_h, int boxes, int classes, float* anchors, int n);
extern "C" __declspec(dllexport) int decodeYOLO(float obj_threshold, float nms_threshold, int* n_out, float* x_out, float* y_out, float* w_out, float* h_out, int* c_out);

#define ERROR_READ_PROTOCOL_BUFFER 1001;
int STATUS = 1;

TF_Buffer* read_file(char* file);
int test_gpu(TF_Session* session);
float sigmoid(float x);
int entry_index(int row, int col, int box, int entry);
float box_iou(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

void free_buffer(void* data, size_t length) {}
static void Deallocator(void* data, size_t length, void* arg) {}


BOOL WINAPI DllMain(
	HINSTANCE hinstDLL, // Handle to DLL module.
	DWORD fdwReason,    // Reason for calling function.
	LPVOID lpReserved)  // Reserved.
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.            
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		TF_CloseSession(session, status);
		TF_DeleteSession(session, status);
		TF_DeleteSessionOptions(sess_opts);
		TF_DeleteImportGraphDefOptions(graph_opts);
		TF_DeleteGraph(graph);
		TF_DeleteStatus(status);

		break;
	}
	return TRUE;
}


__declspec(dllexport) int getVersion(char* tf_version)
{
	sprintf(tf_version, TF_Version());
	return 0;
}

__declspec(dllexport) int setupTF(char* file, int64_t* in_shape, int in_dim, char* in_name, int64_t* out_shape, int out_dim, char* out_name)
{
	graph = TF_NewGraph();
	graph_def = read_file(file);
	graph_opts = TF_NewImportGraphDefOptions();
	status = TF_NewStatus();
	TF_GraphImportGraphDef(graph, graph_def, graph_opts, status);
	if (TF_GetCode(status) != TF_OK) {
		return -1; // ERROR graph import.
	}

	sess_opts = TF_NewSessionOptions();
	status = TF_NewStatus();
	session = TF_NewSession(graph, sess_opts, status);
	if (TF_GetCode(status) != TF_OK) {
		return -2; // ERROR new session.
	}
	
	input_dim = in_dim;
	input_shape = (int64_t*)calloc(input_dim, sizeof(int64_t));
	input_size = 1;
	for (int n = 0; n < input_dim; n++) {
		input_shape[n] = in_shape[n];
		input_size *= in_shape[n];
	}
	values = (float*)calloc(input_size, sizeof(float));
	inputs.push_back({ TF_GraphOperationByName(graph, in_name), 0 });
	input_values.push_back(TF_NewTensor(TF_FLOAT, input_shape, input_dim, values, input_size * sizeof(float), &Deallocator, 0));
	
	output_dim = out_dim;
	output_shape = (int64_t*)calloc(output_dim, sizeof(int64_t));
	output_size = 1;
	for (int n = 0; n < output_dim; n++) {
		output_shape[n] = out_shape[n];
		output_size *= out_shape[n];
	}
	
	outputs.push_back({ TF_GraphOperationByName(graph, out_name), 0 });
	output_values.push_back(TF_AllocateTensor(TF_FLOAT, output_shape, output_dim, output_size * sizeof(float)));	

	if (test_gpu(session)) {
		return 1; // GPU device found.
	}
	else {
		return 0; // No GPU device found.
	}
	
}


__declspec(dllexport) int runTF(float* input_tensor, float* output_tensor) 
{
	input_values.clear();
	input_values.push_back(TF_NewTensor(TF_FLOAT, input_shape, input_dim, input_tensor, input_size * sizeof(float), &Deallocator, 0));
	
	// Run the session.
	TF_SessionRun(session, nullptr,
		&inputs[0], &input_values[0], 1,
		&outputs[0], &output_values[0], 1,
		nullptr, 0, nullptr, status);

	TF_Tensor &out = *output_values[0];
	float* output = (float *)TF_TensorData(&out);

	// Copy to output. 
	for (int i = 0; i < output_size; i++) {
		output_tensor[i] = output[i];
	}
	
	return 0;
}


__declspec(dllexport) int setupDecodeYOLO(int image_w, int image_h, int grid_h, int grid_w, int boxes, int classes, float* anchors, int n_max)
{
	IMAGE_W = image_w;
	IMAGE_H = image_h;
	GRID_W = grid_w;
	GRID_H = grid_h;
	BOXES = boxes;
	CLASSES = classes;
	ANCHORS = (float*)calloc(2*BOXES, sizeof(float));
	ANCHORS = anchors;
	N_MAX = n_max;

	_x = (float*)calloc(N_MAX, sizeof(float));
	_y = (float*)calloc(N_MAX, sizeof(float));
	_w = (float*)calloc(N_MAX, sizeof(float));
	_h = (float*)calloc(N_MAX, sizeof(float));
	_c = (int*)calloc(N_MAX, sizeof(int));
	_score = (float*)calloc(N_MAX, sizeof(float));
	idx_list = (int*)calloc(N_MAX, sizeof(int));
	
	return 0;

}

// Decode the YOLO output tensor. See the YOLO papers for details.
__declspec(dllexport) int decodeYOLO(float obj_threshold, float iou_threshold, int* n_out, float *x_out, float *y_out, float *w_out, float *h_out, int* c_out)
{
	TF_Tensor &out = *output_values[0];
	float* output_tensor = (float *)TF_TensorData(&out);

	int _n = 0;
	for (int row = 0; row < GRID_W; row++) {
		for (int col = 0; col < GRID_H; col++) {
			for (int box = 0; box < BOXES; box++) {
				int obj_idx = entry_index(row, col, box, 4);
				float objectness = sigmoid(output_tensor[obj_idx]);
				if (objectness > obj_threshold) {
					int box_idx = entry_index(row, col, box, 0);
					float x = output_tensor[box_idx];
					float y = output_tensor[box_idx + 1];
					float w = output_tensor[box_idx + 2];
					float h = output_tensor[box_idx + 3];
					int class_idx = entry_index(row, col, box, 5);
					int class_max_idx = 0;
					float class_max = sigmoid(output_tensor[class_idx]);
					for (int c = 1; c < CLASSES; c++) {
						if (sigmoid(output_tensor[class_idx + c]) > class_max) {
							class_max = sigmoid(output_tensor[class_idx + c]);
							class_max_idx = c;
						}
					}
					if (_n < N_MAX) {
						_x[_n] = (row + sigmoid(x)) / GRID_W; // x center, units of image width
						_y[_n] = (col + sigmoid(y)) / GRID_H; // y center, units of image height
						_w[_n] = ANCHORS[2 * box] * exp(w) / GRID_W;
						_h[_n] = ANCHORS[2 * box + 1] * exp(h) / GRID_H;
						_c[_n] = class_max_idx;
						_score[_n] = class_max;
						_n++;
					}
				}
			}
		}
	}
	
	// Supress non-maximum bounding boxes using intersection over union (iou) threshold.
	for (int c = 0; c < CLASSES; c++) {
		int idx_max = 0;
		for (int i = 0; i < _n; i++) {
			if (_c[i] == c) {
				idx_list[idx_max] = i;
				idx_max++;
			}
		}
		for (int i = 0; i < idx_max; i++) {
			int idx_i = idx_list[i];
			for (int j = i + 1; j < idx_max; j++) {
				int idx_j = idx_list[j];
				if (box_iou(_x[idx_i], _y[idx_i], _w[idx_i], _h[idx_i], _x[idx_j], _y[idx_j], _w[idx_j], _h[idx_j]) > iou_threshold) {
					_score[idx_j] = 0;
				}
			}
		}
	}

	// Copy to output. 
	int n = 0;
	for (int i = 0; i < _n; i++) {
		if (_score[i] > 0) {
			x_out[n] = _x[i];
			y_out[n] = _y[i];
			w_out[n] = _w[i];
			h_out[n] = _h[i];
			c_out[n] = _c[i];
			n++;
		}
	}
	*n_out = n;

	return 0;
}


float sigmoid(float x)
{
	return 1. / (1. + exp((float)-x));
}


int entry_index(int row, int col, int box, int entry) 
{
	return entry + (4 + 1 + CLASSES)*(box + BOXES * (row + GRID_H*col));
}


float interval_intersec(float x1, float x2, float  x3, float  x4)
{
	if (x3 < x1) {
		if (x4 < x1)
			return 0;
		else
			return min(x2, x4) - x1;
	}
	else {
		if (x2 < x3)
			return 0;
		else
			return min(x2, x4) - x3;
	}
}


float box_iou(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	float w = interval_intersec(x1 - w1/2, x1 + w1/2, x2 - w2/2, x2 + w2/2);
	float h = interval_intersec(y1 - h1/2, y1 + h1/2, y2 - h2/2, y2 + h2/2);
	float area_intersec = w * h;
	float area_union = w1*h1 + w2*h2 - area_intersec;

	return area_intersec / area_union;
}


TF_Buffer* read_file(char* filename)
{
	TF_Buffer* buf = TF_NewBuffer();

	FILE *f = fopen(filename, "rb");
	if (f) {
		fseek(f, 0, SEEK_END);
		long fsize = ftell(f);
		fseek(f, 0, SEEK_SET);

		void* data = malloc(fsize);
		fread(data, fsize, 1, f);
		fclose(f);

		buf->data = data;
		buf->length = fsize;
		buf->data_deallocator = free_buffer;
	}
	else {
		STATUS= 0;
	}
	return buf;
}


int test_gpu(TF_Session* session) {

	TF_Status* status = TF_NewStatus();
	TF_DeviceList* device_list = TF_SessionListDevices(session, status);

	const int num_devices = TF_DeviceListCount(device_list);
	for (int i = 0; i < num_devices; ++i) {
		const char* device_name = TF_DeviceListName(device_list, i, status);
		const char* device_type = TF_DeviceListType(device_list, i, status);
		if (std::string(device_type) == "GPU") {
			return 1; // GPU device found.
		}
	}
	// No GPU device found.
	return 0;
}

// For debuging.
/*
FILE *f = fopen("Debug.txt", "w");
for (int i = 0; i < 10; i++)
{
fprintf(f, "%.10f\n", output_array[i]);
}
fclose(f);
*/