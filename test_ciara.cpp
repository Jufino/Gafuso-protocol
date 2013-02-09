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
#define vyska_snimania 90
#define sirka_ciary 150
#define offset_y 50
#define obl_y 5
#define meranie_x 2
#define meranie_y 10
#define R_max 100
#define G_max 100
#define B_max 100
#define vykresli 1
float uhol(int x1,int y1,int x2,int y2){
	return atan(((float)y1-(float)y2)/((float)x1-(float)x2))*57.296;
}
int main(void)
{
	CvCapture* camera = cvCaptureFromCAM(0);
//kamera----------------------------
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH,320);
	cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, 240);
//----------------------------------
	int clientsock = vytvor_server(1212);
	IplImage  *img = cvQueryFrame(camera);  
	IplImage  *search = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels );
	printf("Client pripojeny");         
//----------------------------------------
	bool zap = true;
	while(zap == true){  
//-----------------------------------------------------------------------------
		for(int vymaz=0;vymaz != 15;vymaz++){
      			memset(&data[vymaz][0], 0, sizeof(data[vymaz]));
  		}
    		int dlzka = gafuso_recv_array(clientsock,data,1);       
//-----------------------------------------------------------------------------
		if (dlzka != -1){
			if(strcmp(data[0], "img")== 0){
				send_img(clientsock,img,50);
                                send_img(clientsock,search,100);
			}			
			while (NULL == (img = cvQueryFrame(camera))) printf("problem\n");
                int min_y_L = 9000;
                int min_y_P = 9000;
                int min_x_L = 9000;
                int min_x_P = 9000;
                bool minFirst = true;
                bool ciara = false;
		bool pozicia = false;
		cvZero(search);
                for (int y = img->height / 2 + vyska_snimania/2 + offset_y; y >= (img->height / 2 + vyska_snimania/2 + offset_y-obl_y); y -=1){
                  for (int x = img->width / 2 - sirka_ciary / 2; x <= (img->width / 2 + sirka_ciary / 2); x+=1){
                    CvScalar pixel = cvGet2D(img, y, x);      
                    if (pixel.val[0] < R_max && pixel.val[1] < G_max && pixel.val[2] < B_max){
                                ciara = true;
				CvScalar pixelR = cvGet2D(img, y-meranie_y, x+meranie_x);
                                CvScalar pixelL = cvGet2D(img, y-meranie_y, x-meranie_x);
                                CvScalar pixelU = cvGet2D(img, y-meranie_y, x);
				 if ((pixelL.val[0] > R_max && pixelL.val[1] > G_max && pixelL.val[2] > B_max)&&
                                            (pixelR.val[0] > R_max && pixelR.val[1] > G_max && pixelR.val[2] > B_max)&&
                                            (pixelU.val[0] > R_max && pixelU.val[1] > G_max && pixelU.val[2] > B_max)){
                                                pozicia = true;
						y = (img->height / 2 + vyska_snimania/2 + offset_y-obl_y-1);
						x = (img->width / 2 + sirka_ciary / 2+1);
				}
                    }
                  }
                }
                if (ciara == true && pozicia == true){
                  for (int x = img->width / 2 - sirka_ciary / 2; x < (img->width / 2 + sirka_ciary / 2); x += 2){
                    for (int y = img->height / 2 + vyska_snimania/2 + offset_y; y > (img->height / 2 - vyska_snimania/2 + offset_y); y -= 4){
                      CvScalar pixel = cvGet2D(img, y, x);      
                      if (pixel.val[0] < R_max && pixel.val[1] < G_max && pixel.val[2] < B_max){
                      	if (minFirst == true){
				if(((img->height / 2 - vyska_snimania/2 + offset_y)<(y-meranie_y))&&
				    (img->width / 2 + sirka_ciary / 2) > (x+meranie_x) &&
				    (img->width / 2 - sirka_ciary / 2) < (x-meranie_x)){
					CvScalar pixelR = cvGet2D(img, y-meranie_y, x+meranie_x);
                      			CvScalar pixelL = cvGet2D(img, y-meranie_y, x-meranie_x);
                      			CvScalar pixelU = cvGet2D(img, y-meranie_y, x);
					if ((pixelL.val[0] > R_max && pixelL.val[1] > G_max && pixelL.val[2] > B_max)&&
			    		    (pixelR.val[0] > R_max && pixelR.val[1] > G_max && pixelR.val[2] > B_max)&&
			    		    (pixelU.val[0] > R_max && pixelU.val[1] > G_max && pixelU.val[2] > B_max)){
                          			minFirst = false;
                          			min_y_P = y;
                          			min_x_P = x;
						if (vykresli != 1){
                                                	x = (img->width / 2 + sirka_ciary / 2);
                                                	y = (img->height / 2 - vyska_snimania/2 + offset_y);
                                        	}
					}
				}
				else{
					minFirst = false;
                                       	min_y_P = y;
                                     	min_x_P = x;
					if (vykresli != 1){
						x = (img->width / 2 + sirka_ciary / 2);
						y = (img->height / 2 - vyska_snimania/2 + offset_y);
					}
				}
			}
			if(vykresli == 1){
                        	cvSet2D(search, y-1, x, cvScalar(200, 0, 0));
                        	cvSet2D(search, y+1, x, cvScalar(200, 0, 0));
                        	cvSet2D(search, y, x-1, cvScalar(200, 0, 0));
                        	cvSet2D(search, y, x+1, cvScalar(200, 0, 0));
			}
                      }
                    }
                  }
                  minFirst = true;
                  for (int x = img->width / 2 + sirka_ciary / 2; x > (img->width / 2 - sirka_ciary / 2); x -= 2){
                    for (int y = img->height / 2 + vyska_snimania/2 + offset_y; y > (img->height / 2 - vyska_snimania/2 + offset_y); y -= 4){
                      CvScalar pixel = cvGet2D(img, y, x);      
                      if (pixel.val[0] < R_max && pixel.val[1] < G_max && pixel.val[2] < B_max){
                        if (minFirst == true){
                                if(((img->height / 2 - vyska_snimania/2 + offset_y) < (y-meranie_y))&&
                                    (img->width / 2 + sirka_ciary / 2) > (x+meranie_x) &&
                                    (img->width / 2 - sirka_ciary / 2) < (x-meranie_x)){
                                        CvScalar pixelR = cvGet2D(img, y-meranie_y, x+meranie_x);
                                        CvScalar pixelL = cvGet2D(img, y-meranie_y, x-meranie_x);
                                        CvScalar pixelU = cvGet2D(img, y-meranie_y, x);
                                        if ((pixelL.val[0] > R_max && pixelL.val[1] > G_max && pixelL.val[2] > B_max)&&
                                            (pixelR.val[0] > R_max && pixelR.val[1] > G_max && pixelR.val[2] > B_max)&&
                                            (pixelU.val[0] > R_max && pixelU.val[1] > G_max && pixelU.val[2] > B_max)){
                                                minFirst = false;
                                                min_y_L = y;
                                                min_x_L = x;
						if (vykresli != 1){
							x = (img->width / 2 - sirka_ciary / 2);
							y = (img->height / 2 - vyska_snimania/2 + offset_y);
						}
                                        }
                                }
                                else{
                                        minFirst = false;
                                        min_y_L = y;
                                        min_x_L = x;
					if (vykresli != 1){
                                        	x = (img->width / 2 - sirka_ciary / 2);
                                                y = (img->height / 2 - vyska_snimania/2 + offset_y);
                                        }
                                }
                        }
			if(vykresli == 1){
                        	cvSet2D(search, y-1, x, cvScalar(200, 0, 0));
                        	cvSet2D(search, y+1, x, cvScalar(200, 0, 0));
                        	cvSet2D(search, y, x-1, cvScalar(200, 0, 0));
                        	cvSet2D(search, y, x+1, cvScalar(200, 0, 0));
			}
                      }
                    }
                  }
		  if (min_y_L != 9000 && min_y_P != 9000 && ((min_y_P >= img->height / 2 + vyska_snimania/2 + offset_y-obl_y)||
                     (min_y_L >= img->height / 2 + vyska_snimania/2 + offset_y-obl_y)) ){
                    printf("%f\n",uhol(min_x_L,min_y_L,min_x_P,min_y_P));
                  }
		  if(vykresli == 1)	cvLine(img,cvPoint(min_x_L, min_y_L), cvPoint(min_x_P, min_y_P), CV_RGB(0, 0, 255), 3,0);
                }
                else if(ciara == false){
                  printf("%s\n","bez ciary");
		}
		if(vykresli == 1){
              		cvLine(img,cvPoint(img->width / 2 - sirka_ciary / 2, img->height / 2 - vyska_snimania/2 + offset_y), 
			 	   cvPoint(img->width / 2 - sirka_ciary / 2, img->height / 2 + vyska_snimania/2 + offset_y), CV_RGB(0, 200, 0), 1, 0);
              		cvLine(img,cvPoint(img->width / 2 + sirka_ciary / 2, img->height / 2 - vyska_snimania/2 + offset_y), 
			 	   cvPoint(img->width / 2 + sirka_ciary / 2, img->height / 2 + vyska_snimania/2 + offset_y), CV_RGB(0, 200, 0), 1, 0);
              		cvLine(img,cvPoint(img->width / 2 + sirka_ciary / 2, img->height / 2 - vyska_snimania/2 + offset_y), 
			 	   cvPoint(img->width / 2 - sirka_ciary / 2, img->height / 2 - vyska_snimania/2 + offset_y), CV_RGB(0, 200, 0), 1, 0);
              		cvLine(img,cvPoint(img->width / 2 + sirka_ciary / 2, img->height / 2 + vyska_snimania/2 + offset_y), 
			 	   cvPoint(img->width / 2 - sirka_ciary / 2, img->height / 2 + vyska_snimania/2 + offset_y), CV_RGB(0, 200, 0), 1, 0);
              		cvLine(search,cvPoint(img->width / 2 - sirka_ciary / 2, img->height / 2 - vyska_snimania/2 + offset_y),
	 		    	      cvPoint(img->width / 2 - sirka_ciary / 2, img->height / 2 + vyska_snimania/2 + offset_y), CV_RGB(0, 200, 0), 1, 0);
              		cvLine(search,cvPoint(img->width / 2 + sirka_ciary / 2, img->height / 2 - vyska_snimania/2 + offset_y),
				      cvPoint(img->width / 2 + sirka_ciary / 2, img->height / 2 + vyska_snimania/2 + offset_y), CV_RGB(0, 200, 0), 1, 0);
		}
		}
		else{
			zap = false;
		}
	}
	close(clientsock);
	return 0;
}
