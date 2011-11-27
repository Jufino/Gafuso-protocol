//Socket
#include <netinet/in.h>                                                         
#include <sys/socket.h>                                                         
#include <arpa/inet.h>  
//opencv
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
using namespace cv;
//-----------------------------------------------------------------
//definicia portu pri otvoreni socketu
//#define PORT 1212
//-----------------------------------------------------------------
#ifndef PORT
  #define PORT 1212
#endif 
//-----------------------------------------------------------------
int serversock, clientsock; 
//-----------------------------------------------------------------
void quit(char* msg,int retval);
//-----------------------------------------------------------------
void vytvor_server();
//-----------------------------------------------------------------
void send_data(int socket, char len[]);
//-----------------------------------------------------------------
void send_img(int socket, IplImage *img,int kvalita);
//-----------------------------------------------------------------
void get_data_socket(char prijem[][char_for_array]);
//-----------------------------------------------------------------
void send_data_socket(char odosli[][char_for_array],int pocet_dat);
//-----------------------------------------------------------------
