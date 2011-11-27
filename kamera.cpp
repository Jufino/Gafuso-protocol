#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
char data[15][10];
#define PORT 1212
#include "libprotocol.c"
#include "libsocket.c"
#include "libopencv.c"
#include "libfile.c"

int main()
{
int kvalita = 80;
int min_val,min_hue,min_sat,val_dilate;
int max_val,max_hue,max_sat,val_erode;
data_zo_suboru("data_opencv.txt",data,8);
min_val = atoi(data[0]);   
min_hue = atoi(data[1]);   
min_sat = atoi(data[2]);
max_val = atoi(data[3]);   
max_hue = atoi(data[4]);   
max_sat = atoi(data[5]);
val_erode = atoi(data[6]);
val_dilate = atoi(data[7]); 
CvScalar hsv_min = cvScalar(min_hue,min_sat,min_val,0);
CvScalar hsv_max = cvScalar(max_hue,max_sat,max_val,0);
//kamera----------------------------
cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH, 320);
cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, 240);
//----------------------------------
vytvor_server();
//Opencv  
IplImage  *img,*hsv,*thresholded; 
int depth;
CvSize size;
img = cvQueryFrame(camera);
size = cvGetSize(img);
depth = img->depth;
thresholded = cvCreateImage(size, depth, 1);
hsv = cvCreateImage(size, depth, 3);  
printf("Client pripojeny");         
//----------------------------------------
while(1){  
    	hsv_min = cvScalar(min_hue,min_sat,min_val,0);
	hsv_max = cvScalar(max_hue,max_sat,max_val,0);
//-------------------------------------------------------------------------------
	for(int vymaz=0;vymaz != 15;vymaz++){
      		memset(&data[vymaz][0], 0, sizeof(data[vymaz]));
  	}
    	get_data_socket(data);       
//-------------------------------------------------------------------------------
	if (strcmp(data[0], "procces") == 0){
  		img = cvQueryFrame(camera);
        	najdi_objekt_kvadranty(img,hsv,thresholded,hsv_min,hsv_max,val_erode,val_dilate,9);
		if(strcmp(data[1], "img") == 0){
			send_img(clientsock,img,kvalita);
		}
		else if (strcmp(data[1], "tresh") == 0){
                	send_img(clientsock,thresholded,kvalita);
       		}
       		else if (strcmp(data[1], "hsv") == 0){
        	        send_img(clientsock,hsv,kvalita);
	        }
  	} 
    	else if (strcmp(data[0], "original") == 0){
  		  img = cvQueryFrame(camera);
		  send_img(clientsock,img,kvalita);
  	}             
  	else if (strcmp(data[0], "s_param") == 0){
  		for(int vymaz=0;vymaz != 15;vymaz++){
          		memset(&data[vymaz][0], 0, sizeof(data[vymaz]));
        	}
  		sprintf(data[0], "%d",min_val);
  		sprintf(data[1], "%d",min_hue);
  		sprintf(data[2], "%d",min_sat);
  		sprintf(data[3], "%d",max_val);
  		sprintf(data[4], "%d",max_hue);
  		sprintf(data[5], "%d",max_sat);
  		sprintf(data[6], "%d",val_erode);
  		sprintf(data[7], "%d",val_dilate);   
        	send_data_socket(data,8); 
      }
      else if (strcmp(data[0], "r_param") == 0){
		min_val = atoi(data[1]);   
        	min_hue = atoi(data[2]);   
        	min_sat = atoi(data[3]);
        	max_val = atoi(data[4]);   
        	max_hue = atoi(data[5]);   
        	max_sat = atoi(data[6]);
        	val_erode = atoi(data[7]);
       	 	val_dilate = atoi(data[8]);   
      }
      else if (strcmp(data[0], "hodnota") == 0){
	printf("caka na hodnotuz\n");      
//  	hodnota_pixelu(hsv);
      }
	else if (strcmp(data[0], "save") == 0){
  		for(int vymaz=0;vymaz != 15;vymaz++){
          		memset(&data[vymaz][0], 0, sizeof(data[vymaz]));
        	}
  		sprintf(data[0], "%d",min_val);
  		sprintf(data[1], "%d",min_hue);
  		sprintf(data[2], "%d",min_sat);
  		sprintf(data[3], "%d",max_val);
  		sprintf(data[4], "%d",max_hue);
  		sprintf(data[5], "%d",max_sat);
  		sprintf(data[6], "%d",val_erode);
  		sprintf(data[7], "%d",val_dilate);  
  		data_do_suboru("data_opencv.txt",data,8);
  	}
  	else if (strcmp(data[0], "pixels") == 0){
  		cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH, atoi(data[0]));
	       	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, atoi(data[1]));
	       	kvalita = atoi(data[3]);
  	}
}
close(clientsock);
}


