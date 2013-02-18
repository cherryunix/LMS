#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace cv;
using namespace std;

Mat _croped_frame;
namespace lms_var
{
int frame_number = 2,kf_count=1,Step;
char filename[100],keyframe_num[10];
int upperCol = 0, upperRow = 0, LowerCol = 0, LowerRow = 0, datasum = 0;
int row_counter, col_counter, flag_function_call = 0;
float mean_thresh;
int mean_pix_value,s_data,crop_data;
static int crop_values[10],coun_t,_irows,_icols;
}
using namespace lms_var;

class lms
{

public:
	Mat _canny_edge(Mat _Cframe, char* _keyframe);

private:
	Mat _gray_image, _canny_image;
	int ScalingFactor, PixelLength;
	float NoOfSteps, LengthOfvehicle;
};


class keyframe:public lms
{

public:
  keyframe();
  int _compare_detect(Mat pFrame);

private:
  int flag_detect;
  Mat _frame,_gray_image,_canny_image;

};
