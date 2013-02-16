#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace cv;

#include "gafuso.h"

int main(void)
{
	CvCapture* camera = cvCaptureFromCAM(0);
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH,320);
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, 240);
	int clientsock = gafuso_create(1212);
	IplImage  *img = cvQueryFrame(camera);       
	while(1){  
    		gafuso_recv(clientsock,data);       
		if(strcmp(gafuso_load(), "img") == 0)	send_img(clientsock,img,50);
		while (NULL == (img = cvQueryFrame(camera))) printf("problem\n");
	}
	gafuso_close(clientsock);
	return 0;
}
