#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace cv;

char data[15];
#include "libprotocol.h"
#include "libsocket.h"

int main(void)
{
	CvCapture* camera = cvCaptureFromCAM(0);
//kamera----------------------------
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH,320);
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, 240);
//----------------------------------
	int clientsock = vytvor_server(1212);
	IplImage  *img = cvQueryFrame(camera);
//	IplImage *vystup = cvCreateImage(cvSize(160,120),IPL_DEPTH_8U, 3);
//	cvResize(img, vystup,CV_INTER_LINEAR);  
	printf("Client pripojeny");         
//----------------------------------------
	while(1){  
//-----------------------------------------------------------------------------
      		memset(&data[0], 0, sizeof(data));
    		int dlzka = recv(clientsock,data,3,0);      
//-----------------------------------------------------------------------------
		//printf("%s\n",data[0]);
		if (dlzka != -1){
			if(strcmp(data, "img")== 0){
				send_img(clientsock,img,10);
				while (NULL == (img = cvQueryFrame(camera)));
				//cvResize(img, vystup,CV_INTER_LINEAR);
			}		
		}
	}
	close(clientsock);
	return 0;
}
