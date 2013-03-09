#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include "gafuso.h";
#include "libserial.h";

//-----------------------------------------------------------
int main(void)
{
  	int port_int = SerialOpen("/dev/ttyACM1",B9600); 
 	int clientsock = GafusoCreate(1213);
	int zap = 1;
	char *prijem;
	char data[10];
	while(zap){
		GafusoRecv(clientsock);
//		printf("protocol - %s\n",GafusoLoad('f'));
		if (strcmp(GafusoLoad('f'), "data") == 0){
//			printf("OK");
			SerialWrite(port_int,"data\n");
			prijem = SerialRead(port_int,28);
			for(unsigned int o=0;o<28;o++){	
				sprintf(data,"%d",prijem[o]);
				GafusoAdd(data,strlen(data));
			}		
			GafusoSend(clientsock);
			GafusoBuffDel();
		}
/*
		else {
                	write_serial(port_int,GafusoFirstLoad());
                	write_serial(port_int,"\n");
			for(unsigned int o=1;o!=atoi(GafusoLoad());o++){
				write_serial(port_int,GafusoLoad);
				write_serial(port_int,"\n");
			}
		}
*/
	}
 GafusoClose(clientsock);
 return 0;
}
