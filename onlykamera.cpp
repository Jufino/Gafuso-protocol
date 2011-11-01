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
	int PORT = 1212;
	CvCapture* camera = cvCaptureFromCAM(0);
//kamera----------------------------
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, 240);
//----------------------------------
	int clientsock = vytvor_server(PORT);
//Opencv  
	IplImage  *img = cvQueryFrame(camera);  
	printf("Client pripojeny");         
//----------------------------------------
	while(1){  
//-------------------------------------------------------------------------------
		for(int vymaz=0;vymaz != 15;vymaz++){
      			memset(&data[vymaz][0], 0, sizeof(data[vymaz]));
  		}
    		get_data_socket(clientsock,data);       
//-----------------------------------------------------------------------------
  		img = cvQueryFrame(camera);
        	if(strcmp(data[0], "img") == 0){
			send_img(clientsock,img,80);
		} 
	}
	close(clientsock);
	return 0;
}
