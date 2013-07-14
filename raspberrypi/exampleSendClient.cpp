#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <gafuso.h>

using namespace std;

int main(void){
	int clientsock = GafusoConnect("192.168.1.1",1213); //Create Gafuso Client with IP "192.168.1.1" and port 1213
	GafusoAdd("100",3);		     //Add "100" to Gafuso
    	GafusoAdd("200",3);		     //Add "200" to Gafuso
	GafusoAdd("400",3);		     //Add "400" to Gafuso
	GafusoSend(clientsock);		     //Send all add data
	GafusoBuffDel();		     //Delete date from Gafuso buffer
	GafusoClose(clientsock);	     //Close Gafuso Server
	return 0;
}
