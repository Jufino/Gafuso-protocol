#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace cv;

char data[15][10];
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
	printf("Client pripojeny");         
//----------------------------------------
	while(1){  
//-----------------------------------------------------------------------------
		for(int vymaz=0;vymaz != 15;vymaz++){
      			memset(&data[vymaz][0], 0, sizeof(data[vymaz]));
  		}
    		int dlzka = gafuso_recv_array(clientsock,data,1);       
//-----------------------------------------------------------------------------
		//printf("%s\n",data[0]);
		if (dlzka != -1){
//			printf("%s\n",data[0]);
			if(strcmp(data[0], "img")== 0)send_img(clientsock,img,50);
			while (NULL == (img = cvQueryFrame(camera))) printf("problem\n");
		}
	}
	close(clientsock);
	return 0;
}
