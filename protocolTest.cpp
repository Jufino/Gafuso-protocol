#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#define char_for_array 10
#include "libprotocol.c";
#include "libsocket.c";
#include "libspec.c";

void socket_read(char *prijem){
  	recv(clientsock, prijem, 2, 0);
}

//-----------------------------------------------------------
int main(void)
{
//--------Vytvor server a pripoj-----------------------------
	vytvor_server();
//-----------------------------------------------------------
	int N = 50;
	char data_odosli[N][char_for_array];   //pole pre odosielanie
//-------mazanie polii---------------------------------------
	for (int o=0;o<sizeof(data_odosli)/sizeof(data_odosli[0]);o++){
		memset(&data_odosli[o], 0, sizeof(data_odosli[o])); 
	}  
//-----------------------------------------------------------
	while(1) {
		char input_data[2];
		socket_read(input_data);     //data zo socketu
		if (strcmp(input_data, "d") == 0){
			for(int q=0;q < N;q++){
				sprintf(data_odosli[q],"5000");
			}	
			send_data_socket(data_odosli,N);
		}
	}
//---------------------------------------------------
	return 0;
}

