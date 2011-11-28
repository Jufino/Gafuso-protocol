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
//-----------------------------------------------------------
int main(void)
{
//--------Vytvor server a pripoj-----------------------------
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
		for(int q=0;q <15;q++){
			sprintf(data_odosli[q],"%d",q);
		}	
//------------------------------------
		send_data_socket(data_odosli,15);
	}
//---------------------------------------------------
	return 0;
}

