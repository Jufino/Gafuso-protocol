#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#define char_for_array_serial 10
#include "serial.c";
//--------------------------------------------

int main(void)
{
  char prijemx[2][char_for_array_serial];
  char prijemxd[16][char_for_array_serial];
  for (int o=0;o<sizeof(prijemx)/sizeof(prijemx[0]);o++){
		memset(&prijemx[o], 0, sizeof(prijemx[o])); 
	}  
  for (int o=0;o<sizeof(prijemxd)/sizeof(prijemxd[0]);o++){
		memset(&prijemxd[o], 0, sizeof(prijemxd[o])); 
	}  
//--------Vytvor server a pripoj-----------------------------
  port_int = open_serial("/dev/ttyS2",B115200); 
  printf("Serial port open - /dev/ttyS2\n");
//-----------------------------------------------------------
while(1){
  sprintf(prijemx[0],"%s","data");
  sprintf(prijemx[1],"%s","100");  
  send_data_serial(prijemx,2);
  char prijem_data[128];
  memset(&prijem_data, 0, sizeof(prijem_data));  
  read(port_int,&prijem_data,128);
  printf(prijem_data);
  printf("\n");
  }
//------------------------------  -----------------------------
	return 0;
}

