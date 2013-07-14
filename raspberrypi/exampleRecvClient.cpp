#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <gafuso.h>

using namespace std;

int main(void){
	int clientsock = GafusoConnect("192.168.1.1",1213); //Create Gafuso Client with IP "192.168.1.1" and port 1213
	GafusoRecv(clientsock);		     //Receive data from Gafuso
	printf("%s\n",GafusoLoad('f'));	     //Print first data add to Gafuso
	GafusoClose(clientsock);	     //Close Gafuso Server
	return 0;
}
