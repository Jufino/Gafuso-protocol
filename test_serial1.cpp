#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#define char_for_array_serial 10
#include "libprotocol.c";
#include "libserial.c";
#include "libtime.c";
//--------------------------------------
int main(void)
{
//--------Vytvor server a pripoj-----------------------------
  	port_int = open_serial("/dev/ttyO2",B115200); 
  	printf("Serial port open - /dev/ttyO2\n");
//-----------------------------------------------------------
	char odosli_data[2][10];
	for (int clear=0;clear != 2;clear++){
		memset(&odosli_data[clear],0,sizeof(odosli_data[clear]));
	}	
	sprintf(odosli_data[0],"%s","data");
	sprintf(odosli_data[1],"%s","100");  
	send_data_serial(odosli_data,2);
//-----------------------------------------------------------
	msleep(8);
	char prijem_data[20][10];
        for (int clear=0;clear != 20;clear++){
                memset(&prijem_data[clear],0,sizeof(prijem_data[clear]));
        }
  	receive_data_serial(prijem_data);
	for(int i=0;i<20;i++){
		printf(prijem_data[i]);
		printf("\n");	
	}
//------------------------------  -----------------------------
	return 0;
}
