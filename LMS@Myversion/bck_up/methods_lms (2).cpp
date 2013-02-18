#include "classes_namespaces.h"
/**********************************************************
*	Process->Function for canny edge detction(class LMS)  *
***********************************************************/
Mat lms::_canny_edge(Mat _Cframe, char* _keyframe)
{

cvtColor(_Cframe,_gray_image, CV_RGB2GRAY); // converting extracted object to
										   // gray image
Canny(_gray_image,_canny_image, 180, 200);
if(_keyframe == "keyframe")
{
 _croped_frame = _canny_image(Rect(crop_values[5], crop_values[6],crop_values[7],crop_values[8]));
 return (_croped_frame);
}

_gray_image = _gray_image(Rect(crop_values[0], crop_values[1], crop_values[2],crop_values[3]));

// writting canny image and computing step size
	Step = crop_values[4];
    imwrite("C:/AVC/canny_image.jpg",_canny_image);

// reading rows and columns from gray image
	_irows = _gray_image.rows;
	_icols = _gray_image.cols;
	return (_canny_image);
}
