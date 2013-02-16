#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include "gafuso.h";
#include "gpio.h"
//-----------------------------------------------------------
int main(void){
 	int clientsock = gafuso_create(1213);
	gafuso_add("100");
     	gafuso_add("200");
	gafuso_add("400");
	gafuso_send(clientsock);
//	gafuso_recv(clientsock);
//	char *data = gafuso_load();
//	printf("%s\n",data);
//	data = gafuso_load();
//	printf("%s\n",data);
	gafuso_close(clientsock);
	return 0;
}

