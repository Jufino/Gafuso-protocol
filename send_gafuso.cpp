#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include "gafuso.h";
#include "libserial.h"; 
//-----------------------------------------------------------
int main(void){
//	int clientsock = GafusoCreate(1213);
//	GafusoAdd("100");
  //   	GafusoAdd("200");
//	GafusoAdd("400");
//	GafusoSend(10);//clientsock);
//	GafusoBuffDel();
  //      GafusoAdd("500");
    //    GafusoAdd("600");
//	GafusoSend(10);
int port_int = SerialOpen("/dev/ttyACM1",B9600); 
char *test;
int x=0;
//for(int x=0;x<5;x++){
	SerialWrite(port_int,"data\n");
	test = SerialRead(port_int,28);
		for(int i=0;i<28;i++){
			printf("%d,  -  %d\n",i,test[i]);
		}
		x=0;
//}
SerialClose(port_int);
//	while(1){	
//		GafusoRecv(clientsock);
//		printf("%s\n",GafusoLoadFirst());
//		printf("%s\n",GafusoLoad());
//	}
//	GafusoClose(clientsock);
	return 0;
}

