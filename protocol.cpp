#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#define char_for_array 10
#define char_for_array_serial 10
#include "libprotocol.c";
#include "libsocket.c";
#include "libserial.c"; 
#include "libspec.c";
//-----------------------------------------------------------
int main(void)
{

//--------Vytvor server a pripoj-----------------------------
  port_int = open_serial("/dev/ttyO2",B115200); 
  printf("Serial port open - /dev/ttyO2\n");
  vytvor_server();
//-----------------------------------------------------------
  char prijemx[40][char_for_array];   //pole pre prijem dat 
  char prijem_serial[40][char_for_array];   //pole pre prijem dat
//-------mazanie polii---------------------------------------
	for (int o=0;o<sizeof(prijemx)/sizeof(prijemx[0]);o++){
		memset(&prijemx[o], 0, sizeof(prijemx[o])); 
	}  
	for (int o=0;o<sizeof(prijem_serial)/sizeof(prijem_serial[0]);o++){
		memset(&prijem_serial[o], 0, sizeof(prijem_serial[o])); 
	}  
//-----------------------------------------------------------
  get_data_socket(prijemx);     //data zo socket
//-----------------------------------------------------------
//-----------------------------------------------------------
  if (strcmp(prijemx[0], "data") == 0){
    send_data_serial(prijemx,2);
    receive_data_serial(prijem_serial);
    send_data_socket(prijem_serial,15);
  }
  else if (strcmp(prijemx[0], "hovo") == 0){
    precitaj_text(prijemx[1]);
    printf(prijemx[1]);
  }
  else{
//-----------------------------------------------------------
    send_data_serial(prijemx,2);
  }
//---------------------------------------------------

//-----------------------------------------------------------
	return 0;
}

