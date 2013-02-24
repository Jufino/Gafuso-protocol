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
  	int port_int = open_serial("/dev/ttyO2",B115200); 
 	int clientsock = GafusoCreate(1213);
	int zap = 1;
	char prijem_serial[128];
	while(zap){
        	memset(&prijem_serial, 0, sizeof(prijem_serial));
		GafusoCreate(clientsock);
		if (strcmp(GafusoFirstLoad(), "data") == 0){
			write_serial(port_int,GafusoFirstLoad());
			write_serial(port_int,"\n");
			int pocet = atoi(GafusoLoad());
			read(port_int, prijem_serial,atoi(pocet+10);  
			for(unsigned int o=0;o!=pocet;o++){	
				char *data = NULL;
				sprintf(data,"%d",prijem_serial[o]);
				GafusoAdd(data);
			}		
			GafusoSend(clientsock);
		}
		else {
                	write_serial(port_int,GafusoFirstLoad());
                	write_serial(port_int,"\n");
			for(unsigned int o=1;o!=atoi(GafusoLoad());o++){
				write_serial(port_int,GafusoLoad);
				write_serial(port_int,"\n");
			}
		}
	}
 GafusoClose(clientsock);
 return 0;
}
