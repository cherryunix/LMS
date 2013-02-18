file_procedures
ifstream myfile("C:/AVC/settings.txt");
if (myfile.is_open()) 
{
	while (myfile >> crop_data && coun_t <=10 ) 
	{
			crop_values[coun_t] = crop_data;
			coun_t++;
	}
		myfile.close();
}
	
//for l_cannyedge
ifstream myfile("C:/AVC/settings.txt");
if (myfile.is_open()) 
 {
	while (myfile >> crop_data && coun_t <= 10) 
	{
			crop_values[coun_t] = crop_data;
			coun_t++;
	}
		myfile.close();
 }	
	