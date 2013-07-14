#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <gafuso.h>

using namespace std;

int main(void){
	int clientsock = GafusoCreate(1213); //Create Gafuso Server with local IP and port 1213
	GafusoRecv(clientsock);		     //Receive data from Gafuso
	printf("%s\n",GafusoLoad('f'));	     //Print first data add to Gafuso
	GafusoClose(clientsock);	     //Close Gafuso Server
	return 0;
}
