#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace cv;
using namespace std;

/*****************************************************
*	Class for Length Measurment System				 *
******************************************************/

class lms
{

public:
	Mat _canny_edge(Mat _Cframe, char* _keyframe);
	lms();
	Mat  _croped_frame;
	int  Step;
	char filename[100],keyframe_num[10];
	int  mean_pix_value,s_data,crop_data;

private:
	Mat   _gray_image, _canny_image;
	int   ScalingFactor, PixelLength,datasum;
	float NoOfSteps, LengthOfvehicle;
	int   row_counter, col_counter,LowerRow;
	int   upperCol, upperRow, LowerCol,crop_values[10],coun_t;
	int   _irows,_icols;
};

/*****************************************************
*	Class for Keyframe Detection				     *
******************************************************/
class keyframe:public lms
{

public:
  keyframe();
  int _compare_detect(Mat pFrame);

private:
  int _flag_detect;
  float mean_thresh;
  Mat _frame,_gray_image,_canny_image;

};
