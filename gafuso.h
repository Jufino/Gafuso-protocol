#ifndef _GAFUSO_H
#define _GAFUSO_H

#include <netinet/in.h>                                                         
#include <sys/socket.h>                                                         
#include <arpa/inet.h>  
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

using namespace cv;

//------------------------------------------------------------------------------------- 
int GafusoCreate(int PORT);
//-------------------------------------------------------------------------------------
void GafusoClose(int PORT);
//-------------------------------------------------------------------------------------
int GafusoConnect(char hostname[],int PORT);
//-------------------------------------------------------------------------------------
void GafusoAdd(char *data_to_add);
//-------------------------------------------------------------------------------------
void GafusoSend(int socket);
//-------------------------------------------------------------------------------------
void GafusoRecv(int socket);
//-------------------------------------------------------------------------------------
char *GafusoLoadFirst(void);
//-------------------------------------------------------------------------------------
char *GafusoLoad(void);
//-------------------------------------------------------------------------------------
void GafusoSendImg(int socket,IplImage *img, int kvalita);
//-------------------------------------------------------------------------------------
#endif
