#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;
#include "gafuso.h";

int main(void){
	int clientsock = GafusoCreate(1213);
	GafusoRecv(clientsock);
	printf("%s",GafusoLoad('n'));
	GafusoAdd("100",3);
    	GafusoAdd("200",3);
	GafusoAdd("400",3);
	GafusoSend(clientsock);
	GafusoBuffDel();
	GafusoClose(clientsock);
	return 0;
}
