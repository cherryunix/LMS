/*****************************************************
*	   Capture->Function for live capturing			 *
******************************************************/
_live_capturing()
{

	int flag_detect = 0; // condition varable for breaking loop

	VideoCapture capture("rtsp://192.168.1.110:554"); // capture live from network
	VideoCapture capture("Test5.avi"); // capture from recorded video	

	while (1) 
	{		
		capture.read(frame);  // reading frame from live video stream
		imshow("LIVE",frame); // dispalying frame continiously				
		waitKey(25); //delay of 25milisec	
		compare_detect(frame); // function to detect key frame
		if(flag_detect!=0)
		break;
	}
}
//End of function



/*****************************************************
*	Process->Function for detection of Keyframe				 *
******************************************************/
_compare_detect(Mat pFrame) 
{

croped_frame = pFrame(Rect(crop_values[5], crop_values[6],crop_values[7],crop_values[8]));;
croped_frame = k_canny_edge(croped_frame);

// computing threshold value of each frame to detect key frame
	Scalar dyn_thresh = mean(croped_frame);
	Mat me_an(1, 1, CV_8UC1, dyn_thresh);
	uchar* pix_data = me_an.ptr<uchar>(0);
	mean_pix_value = pix_data[0];

// comparing frame subsequently
	if (mean_pix_value >= (mean_thresh + 5) && flag_function_call != 0) 
	{
		cout << "detected" << endl; 		
		imwrite("C:/AVC/keyframe.jpg", pFrame);// writting keyframe
		kf_count++;
		flag_detect++;
	}

	mean_thresh = mean_pix_value;
	flag_function_call++;
	cout << flag_detect << endl;
	return (flag_detect);
}
// End of function



/*****************************************************
*	Process->Function for canny edge detction(class LMS)  *
******************************************************/
_lcanny_edge(Mat c_image) 
{

cvtColor(c_image, gray_image, CV_RGB2GRAY); // converting extracted object to 
										   // gray image
gray_image = gray_image(Rect(crop_values[0], crop_values[1], crop_values[2],
crop_values[3]));

// writting canny image and computing step size
	Step = crop_values[4];
	Canny(gray_image, canny_image, 180, 200);
    imwrite("C:/AVC/canny_image.jpg",canny_image);

// reading rows and columns from gray image
	i_rows = gray_image.rows;
	i_cols = gray_image.cols;
	return (canny_image);
}
// End of function



/**************************************************************
*	Process->Function for canny edge detction(class Keyframe) *
***************************************************************/
_kcanny_edge(Mat k_image) 
{
	cvtColor(k_image, gray_image, CV_RGB2GRAY); // image converted from rgb to gray
	Canny(gray_image, canny_image, 180, 200); // canny edge detection on gray image
	return (canny_image);
}



/*****************************************************
* Compute_length->Function for Length Computation 	 *
******************************************************/
_compute_length() 
 {

// scanning for row & column pixel value to compute the sum of white blocks
   for (row_counter = 0; row_counter < i_rows; row_counter++) 
    {
      uchar* data = canny_image.ptr<uchar>(row_counter);

		for (col_counter = 0; col_counter <= i_cols; col_counter++) 
		{
			datasum = data[col_counter] + datasum;
			if (datasum >= 12648) 
			{
				upperCol = col_counter;
				upperRow = row_counter;
				goto label;
			}
		} 
	} 

// after identifying column number using it to compute length in terms of pixels
  label:
    PixelLength = 288 - upperRow;
	NoOfSteps = 1.0;
	NoOfSteps = (float) PixelLength / (float) Step;
    cout<<NoOfSteps<<endl;


//calibration block which will calibrate pixel according to actual length 
//in terms of cm's

// storing length of vehicle
	LengthOfvehicle = ScalingFactor * NoOfSteps;
	cout<<LengthOfvehicle<<endl;
	cout<<PixelLength<<endl;

 }
// End of function



/*****************************************************
* Storeresults->Function for Storing Results 		 *
******************************************************/
_store_results() 
{
	ofstream avc;
	time_t now = time(0);
	char* dt = ctime(&now);
	char filename[20];
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time(&rawtime);

	timeinfo = localtime(&rawtime);// Reading time from system

// Generating log file datewise
	strftime(buffer,80,"%d-%m-%y",timeinfo);
	strcpy(filename,"C:/AVC/");
	strcat(filename,buffer);
	strcat(filename,".txt");
	avc.open(filename, ios::app);
	strftime(buffer,80,"%H%Mhrs",timeinfo);
	avc<<buffer<<"\t"<<LengthOfvehicle<<endl;
	avc.close();

// Writing results into file with anlytical parameters
	ofstream measure_ment;
	measure_ment.open("C:/AVC/measurement.txt", ios::app);
	measure_ment << "---------------------------------------" << endl;
	measure_ment << "Scaling Factor is -> " << ScalingFactor << endl;
	measure_ment << "Step is -> " << Step << endl;
	measure_ment << "Pixel length is -> " << PixelLength << endl;
	measure_ment << "No. of Steps are -> " << NoOfSteps << endl;
	measure_ment << "Length is ->" << LengthOfvehicle << endl << endl;

	ofstream up_row;
	up_row.open("C:/AVC/upper_row.txt", ios::app);
	up_row << upperRow << endl;
}
