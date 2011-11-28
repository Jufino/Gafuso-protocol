#ifndef _LIBSOCKET_H
#define _LIBSOCKET_H
//Socket
#include <netinet/in.h>                                                         
#include <sys/socket.h>                                                         
#include <arpa/inet.h>  
//OpenCV
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include "libprotocol.h"
using namespace cv;
//----------------------------------------------------------------- 
//-----------------------------------------------------------------
void quit(char* msg,int retval);
//-----------------------------------------------------------------
int vytvor_server(int PORT);
//-----------------------------------------------------------------
void send_data(int socket, char len[]);
//-----------------------------------------------------------------
void send_img(int socket, IplImage *img,int kvalita);
//-----------------------------------------------------------------
void get_data_socket(int socket, char prijem[][char_for_array]);
//-----------------------------------------------------------------
void send_data_socket(int socket, char odosli[][char_for_array],int pocet_dat);
//-----------------------------------------------------------------
#endif
