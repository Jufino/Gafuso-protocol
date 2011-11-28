#ifndef _LIBOPENCV_H
#define _LIBOPENCV_H

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

using namespace cv;

CvCapture* camera = cvCaptureFromCAM(0);
int *najdi_objekt(IplImage  *img, IplImage  *hsv,IplImage  *thresholded,CvScalar hsv_min,CvScalar hsv_max,int erode,int dilate);

int najdi_objekt_kvadranty(IplImage  *img, IplImage  *hsv,IplImage  *thresholded,CvScalar hsv_min,CvScalar hsv_max,int erode,int dilate,int pocet_kvadrantov);

#endif
