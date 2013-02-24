#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include "gafuso.h";
#include "gpio.h"
//-----------------------------------------------------------
int main(void){
 	int clientsock = GafusoCreate(1213);
//	gafuso_add("100");
//     	gafuso_add("200");
//	gafuso_add("400");
//	gafuso_send(clientsock);
	while(1){	
		GafusoRecv(clientsock);
		printf("%s\n",GafusoLoad());
	}
//	gafuso_recv(clientsock);
//	char *data = gafuso_load();
//	printf("%s\n",data);
//	data = gafuso_load();
//	printf("%s\n",data);
	GafusoClose(clientsock);
	return 0;
}

