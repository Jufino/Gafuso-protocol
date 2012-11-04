#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
#define char_for_array 10
#include "libprotocol.h"
#include "libsocket.h"
#include "libtime.h"
#include "libspec.h"
//-----------------------------------------------------------
int main(void)
{
//--------Vytvor server a pripoj-----------------------------
 	int clientsock = vytvor_server(1213);
//-----------------------------------------------------------
	char data[40][char_for_array];   //pole pre prijem dat 
	for(int z=0;z<10;z++){
//-------mazanie polii---------------------------------------
        for(unsigned int o=0;o<sizeof(data)/sizeof(data[0]);o++){
                memset(&data[o], 0, sizeof(data[o]));
	}
//-----------------------------------------------------
	int dlzka = gafuso_recv_array(clientsock, data,40);
	//gafuso_send_array(clientsock, data_prijem);
	if(dlzka != -1){
		for(int i=0;i<dlzka;i++){
			printf("%s\n",data[i]);
		}
	}
	else{
		printf("ziadne nove data\n");
	}
}
//---------------------------------------------------
	close(clientsock);
	return 0;
}

