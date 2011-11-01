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
#include "gpio.h"
//-----------------------------------------------------------
int main(void)
{
//--------Vytvor server a pripoj-----------------------------
 	int clientsock = vytvor_server(1213);
	int zap = 1;
//-----------------------------------------------------------
	char data_prijem[40][char_for_array];   //pole pre prijem dat 
	char data_odosli[40][char_for_array];   //pole pre odosielanie
while(zap){
//-------mazanie polii---------------------------------------
        for(int o=0;o<sizeof(data_prijem)/sizeof(data_prijem[0]);o++){
                memset(&data_prijem[o], 0, sizeof(data_prijem[o]));
	}
        for(int o=0;o<sizeof(data_odosli)/sizeof(data_odosli[0]);o++){
                memset(&data_odosli[o], 0, sizeof(data_odosli[o]));
	}
//-----------------------------------------------------
	gafuso_recv_array(clientsock, data_prijem);     //data zo socketu
//-----------------------------------------------------------
	printf("0. - ");
	printf(data_prijem[0]);
	printf("\n");
	printf("1. - ");
	printf(data_prijem[1]);
	printf("\n");
	printf("2. - ");        
	printf(data_prijem[2]);
        printf("\n");       
        printf("3. - "); 
	printf(data_prijem[3]);
        printf("\n");
        printf("4. - ");        
	printf(data_prijem[4]);
        printf("\n");
        printf("5. - ");        
	printf(data_prijem[5]);
        printf("\n");
	gafuso_send_array(clientsock,data_prijem,2);
//---------------------------------------------------
}
	close(clientsock);
	return 0;
}

