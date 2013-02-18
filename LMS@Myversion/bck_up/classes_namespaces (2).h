// classes and namespaces
namespace lms_mod 
{
Mat resultant_out, croped_frame, frame;
int frame_number = 2,kf_count=1,Step;
char filename[100],keyframe_num[10];
int upperCol = 0, upperRow = 0, LowerCol = 0, LowerRow = 0, datasum = 0;
int row_counter, col_counter, flag_function_call = 0;
float mean_thresh;
int mean_pix_value,s_data,crop_data;
static int crop_values[10];
}

using namespace lms_mod;

class lms 
{

public:
	Mat canny_edge(Mat _Cframe, char* _keyframe)
	void compute_length();
	void storeresults();

private:
	Mat gray_image, canny_image, k_image, c_image;
	int i_rows, i_cols, ScalingFactor, PixelLength;
	float NoOfSteps, LengthOfvehicle;
};


class keyframe: public lms 
{

public:
  keyframe(char* IP);
  Mat _canny_edge(Mat c_image, char* _keyframe);

private:
  int flag_detect;
  Mat frame,_gray_image,_canny_image;
  char* ip;
  int _compare_detect(Mat pFrame);
};