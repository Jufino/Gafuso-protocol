#ifndef _LIBOPENCV_H
#define _LIBOPENCV_H

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

#define vyska_snimania 90
#define sirka_ciary 150
#define offset_y 50
#define obl_y 5
#define meranie_x 2
#define meranie_y 10
#define R_max 100
#define G_max 100
#define B_max 100
#define vykresli 0

using namespace cv;

int *najdi_objekt(IplImage  *img, IplImage  *hsv,IplImage  *thresholded,CvScalar hsv_min,CvScalar hsv_max,int erode,int dilate);

int najdi_objekt_kvadranty(IplImage  *img, IplImage  *hsv,IplImage  *thresholded,CvScalar hsv_min,CvScalar hsv_max,int erode,int dilate,int pocet_kvadrantov);
void ciara(char vypis[20],IplImage  *img, IplImage  *search);
#endif
