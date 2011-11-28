#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#define char_for_array 10
#include "libprotocol.h";
#include "libsocket.h";
#include "libspec.h";
#include "libserial.h";
#include "libtime.h";
//-----------------------------------------------------------
int main(void)
{
	int PORT = 1213;
//--------Vytvor server a pripoj-----------------------------
  	int port_int = open_serial("/dev/ttyO2",B115200); 
  	printf("Serial port open - /dev/ttyO2\n");
 	int clientsock = vytvor_server(PORT);
	int zap = 1;
//-----------------------------------------------------------
	char data_prijem[40][char_for_array];   //pole pre prijem dat 
	char data_odosli[40][char_for_array];   //pole pre odosielanie
	char prijem_serial[128];
while(zap){
//-------mazanie polii---------------------------------------
	for (int o=0;o<sizeof(data_prijem)/sizeof(data_prijem[0]);o++){
		memset(&data_prijem[o], 0, sizeof(data_prijem[o])); 
	}  
	for (int o=0;o<sizeof(data_odosli)/sizeof(data_odosli[0]);o++){
		memset(&data_odosli[o], 0, sizeof(data_odosli[o])); 
	} 
 	memset(&prijem_serial, 0, sizeof(prijem_serial));
//-----------------------------------------------------------
	get_data_socket(clientsock, data_prijem);     //data zo socketu
//-----------------------------------------------------------
//-----------------------------------------------------------
	if (strcmp(data_prijem[0], "data") == 0){
		send_data_serial(port_int,data_prijem,2);
		read(port_int,&prijem_serial,128);
		for(int o=0;o<11;o++){
			sprintf(data_odosli[o],"%d",prijem_serial[o]);
		}
		send_data_socket(clientsock, data_odosli,11);
		
	}
	else if(strcmp(data_prijem[0],"prikaz") == 0){
		for(int o=0; o<strlen(data_prijem[1]); o++)
			data_odosli[0][o]=data_prijem[1][o];
		send_data_serial(port_int, data_odosli,1);
	}
	else if(strcmp(data_prijem[0],"vyp") == 0)	zap =0;
	else						send_data_serial(port_int, data_prijem,2);

//---------------------------------------------------
}
	return 0;
}

