#include "libopencv.h"
//-------------------------------------------------------------------------------
int *najdi_objekt(IplImage  *img, IplImage  *hsv,IplImage  *thresholded,CvScalar hsv_min,CvScalar hsv_max,int erode,int dilate){
    int minx,miny,maxx,maxy;
    static int suradnice[4];
    img = cvQueryFrame(camera);
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
