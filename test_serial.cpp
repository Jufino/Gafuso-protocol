#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#define char_for_array_serial 10
#include "libprotocol.c";
#include "libserial.c";
//--------------------------------------------

int main(void)
{
//--------Vytvor server a pripoj-----------------------------
  port_int = open_serial("/dev/ttyO2",B115200); 
  printf("Serial port open - /dev/ttyO2\n");
//-----------------------------------------------------------
while(1){
	char prijemx[2][10];
	  sprintf(prijemx[0],"%s","data");
	sprintf(prijemx[1],"%s","100");  
	send_data_serial(prijemx,2);
  	char prijem_data[128];
  	int i=0;
	memset(&prijem_data, 0, sizeof(prijem_data));  
  	i = read(port_int,&prijem_data,128);
	printf("%d\n",prijem_data[0]);
  }
//------------------------------  -----------------------------
	return 0;
}
