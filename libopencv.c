#include "libopencv.h"
//----------------------------------------------------------------------
int *najdi_objekt(IplImage  *img, IplImage  *hsv,IplImage  *thresholded,CvScalar hsv_min,CvScalar hsv_max,int erode,int dilate){
    int minx,miny,maxx,maxy;
    static int suradnice[4];
    cvZero(thresholded);
    cvZero(hsv);
    cvCvtColor( img, hsv, CV_BGR2HSV );
    cvInRangeS(hsv, hsv_min, hsv_max, thresholded);
    if (erode != 0) cvErode( thresholded, thresholded, NULL, erode);
    if (dilate != 0) cvDilate( thresholded, thresholded, NULL, dilate);
    minx = 5000;
    miny = 5000;
    maxx = 0;
    maxy = 0;
    for (int x=0;img->width!=x;x++){
      for(int y=0;img->height!=y;y++){
	       if (cvGet2D(thresholded,y,x).val[0] == 255 ){
	           if (minx > x) minx = x;
	           if (miny > y) miny = y;
	           if (maxx < x) maxx = x;
	           if (maxy < y) maxy = y;
	       } 
      }
    } 
    cvRectangle(img, cvPoint(minx,miny), cvPoint(maxx,maxy), cvScalar(255,0,0), 1);
    suradnice[0] = minx;
    suradnice[1] = miny;
    suradnice[2] = maxx;
    suradnice[3] = maxy;
    return suradnice;
}
//-----------------------------------------------------------------------------------
int najdi_objekt_kvadranty(IplImage  *img, IplImage  *hsv,IplImage  *thresholded,CvScalar hsv_min,CvScalar hsv_max,int erode,int dilate,int pocet_kvadrantov){
    int minx,miny,maxx,maxy;
    int sirka[pocet_kvadrantov],sirka_max=-1;
    cvZero(thresholded);
    cvZero(hsv);
    cvCvtColor( img, hsv, CV_BGR2HSV );
    cvInRangeS(hsv, hsv_min, hsv_max, thresholded);
    if (erode != 0) cvErode( thresholded, thresholded, NULL, erode);
    if (dilate != 0) cvDilate( thresholded, thresholded, NULL, dilate);
    int dlzka_kvadrantu = img->width / pocet_kvadrantov;
    int x=0;
    int kvad_x = dlzka_kvadrantu;
    for (int poc_kvadrant=0;poc_kvadrant!=pocet_kvadrantov;poc_kvadrant++){
      minx = 5000;
      miny = 5000;
      maxx = 0;
      maxy = 0;
      for (x=kvad_x-dlzka_kvadrantu;kvad_x!=x;x++){
        for(int y=0;img->height!=y;y++){
  	       if (cvGet2D(thresholded,y,x).val[0] == 255 ){
  	           if (minx > x) minx = x;
  	           if (miny > y) miny = y;
  	           if (maxx < x) maxx = x;
  	           if (maxy < y) maxy = y;
  	       } 
        }
      } 
      sirka[poc_kvadrant] = maxx-minx;
      kvad_x = kvad_x + dlzka_kvadrantu;
      cvRectangle(img, cvPoint(minx,miny), cvPoint(maxx,maxy), cvScalar(255,0,0), 1);
    }
    pocet_kvadrantov = pocet_kvadrantov/2;
    for(x = 0;x !=pocet_kvadrantov;x++){
      if (sirka[x] >= sirka_max){
        sirka_max = x;
      }
      if (sirka[(pocet_kvadrantov*2)-x] >= sirka_max){
        sirka_max = (pocet_kvadrantov*2)-x;
      } 
    }
      if (sirka[pocet_kvadrantov] >= sirka_max){
        sirka_max = pocet_kvadrantov;
      } 
    return sirka_max;
}
//-----------------------------------------------------------------
int uhol(int x1,int y1,int x2,int y2){
	return atan(((float)y1-(float)y2)/((float)x1-(float)x2))*5729;
}
//-----------------------------------------------------------------
void ciara(char vypis[20],IplImage  *img, IplImage  *search){		
		int min_y_L = 9000;
                int min_y_P = 9000;
                int min_x_L = 9000;
                int min_x_P = 9000;
                bool minFirst = true;
                bool ciara = false;
		bool pozicia = false;
		if(vykresli == 1)	cvZero(search);
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
                    	sprintf(vypis,"%i\n",uhol(min_x_L,min_y_L,min_x_P,min_y_P));
                  }
		  if(vykresli == 1)	cvLine(img,cvPoint(min_x_L, min_y_L), cvPoint(min_x_P, min_y_P), CV_RGB(0, 0, 255), 3,0);
                }
                else if(ciara == false){
		  	sprintf(vypis,"%s\n","X");
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
