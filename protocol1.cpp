#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#define char_for_array 10
#define char_for_array_serial 10
#include "libprotocol.c";
#include "libsocket.c";
#include "libspec.c";
#include "libserial.c";
#include "libtime.c";
//-----------------------------------------------------------
int main(void)
{
//--------Vytvor server a pripoj-----------------------------
  	port_int = open_serial("/dev/ttyO2",B115200); 
  	printf("Serial port open - /dev/ttyO2\n");
	vytvor_server();
//-----------------------------------------------------------
	char data_prijem[40][char_for_array];   //pole pre prijem dat 
	char data_odosli[40][char_for_array];   //pole pre odosielanie
//-------mazanie polii---------------------------------------
	for (int o=0;o<sizeof(data_prijem)/sizeof(data_prijem[0]);o++){
		memset(&data_prijem[o], 0, sizeof(data_prijem[o])); 
	}  
	for (int o=0;o<sizeof(data_odosli)/sizeof(data_odosli[0]);o++){
		memset(&data_odosli[o], 0, sizeof(data_odosli[o])); 
	}  
//-----------------------------------------------------------
	get_data_socket(data_prijem);     //data zo socket
//-----------------------------------------------------------
//-----------------------------------------------------------
	if (strcmp(data_prijem[0], "data") == 0){
//napriklad chceme poslat 15 dat - vlozime si ich do pola
		send_data_serial(data_prijem,1);
		msleep(8);	
		receive_data_serial(data_odosli);
//------------------------------------
		send_data_socket(data_odosli,12);
	}
//---------------------------------------------------
	return 0;
}

