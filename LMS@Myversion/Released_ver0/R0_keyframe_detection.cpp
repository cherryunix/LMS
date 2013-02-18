#include "classes_namespaces.h"
/*****************************************************
*	Capture->  Function for live capturing			 *
******************************************************/
keyframe::keyframe()
{

_flag_detect = 0; // condition varable for breaking loop
//VideoCapture capture("rtsp://192.168.1.110:554"); // capture live from network
VideoCapture capture("Test5.avi"); // capture from recorded video

	while (1)
	{
		capture.read(_frame);  // reading frame from live video stream
   _compare_detect(_frame); // function to detect key frame
    if(_flag_detect != 0)
    break;
	}
}
//End of function

/*****************************************************
*	Process->Function for detection of Keyframe		 *
******************************************************/
int keyframe::_compare_detect(Mat pFrame)
{

_croped_frame =_canny_edge(pFrame,"keyframe");
imshow("LIVE",_croped_frame); // dispalying frame continiously
waitKey(25); //delay of 25milisec


// computing threshold value of each frame to detect key frame
	Scalar dyn_thresh = mean(_croped_frame);
	Mat me_an(1, 1, CV_8UC1, dyn_thresh);
	uchar* pix_data = me_an.ptr<uchar>(0);
	mean_pix_value = pix_data[0];

// comparing frame subsequently
	if (mean_pix_value >= (mean_thresh + 5))
	{
		cout << "detected" << endl;
		imwrite("C:/AVC/keyframe.jpg", pFrame);// writting keyframe
		_flag_detect++;
	}

	mean_thresh = mean_pix_value;
	cout <<_flag_detect<< endl;
	return (_flag_detect);

}
// End of function
