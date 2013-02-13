#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace cv;

#include "libopencv.h"
#include "libserial.h"

int main(void)
{
	int port_int = open_serial("/dev/ttyACM1",B9600);
	CvCapture* camera = cvCaptureFromCAM(0);
//kamera----------------------------
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH,320);
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, 240);
//----------------------------------
	IplImage  *img = cvQueryFrame(camera);  
	IplImage  *search = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels );       
//----------------------------------------
	bool zap = true;
	char vypis[20];
	while(zap == true){    
                memset(&vypis, 0, sizeof(vypis));
//-----------------------------------------------------------------------------
		while (NULL == (img = cvQueryFrame(camera))) printf("problem\n");
                ciara(vypis,img,search);
		write_serial(port_int,vypis);
	}
	return 0;
}
