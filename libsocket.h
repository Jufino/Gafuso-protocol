#ifndef _LIBSOCKET_H
#define _LIBSOCKET_H
//Socket
#include <netinet/in.h>                                                         
#include <sys/socket.h>                                                         
#include <arpa/inet.h>  
#include <netdb.h>
#include <unistd.h> // UNIX standard function definitions
#include <errno.h>
//OpenCV
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include "libprotocol.h"

#define recv_timeout 50

using namespace cv;
//----------------------------------------------------------------- 
int vytvor_server(int PORT);
//-----------------------------------------------------------------
int connect(char hostname[],int PORT);
//-----------------------------------------------------------------
void send_data(int socket, char len[]);
//-----------------------------------------------------------------
void send_img(int socket, IplImage *img,int kvalita);
//-----------------------------------------------------------------
int gafuso_recv_array(int socket, char prijem[][char_for_array],unsigned int size);
//-----------------------------------------------------------------
void gafuso_send_array(int socket, char odosli[][char_for_array],unsigned int size);
//-----------------------------------------------------------------
#endif
