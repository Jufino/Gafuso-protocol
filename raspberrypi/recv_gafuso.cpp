#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include "gafuso.h";

int main(void){
	int clientsock = GafusoCreate(1213);
	GafusoRecv(clientsock);
	printf("%s\n",GafusoLoad('f'));
	GafusoClose(clientsock);
	return 0;
}
