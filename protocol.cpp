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
void reset_atmega(){
	gpio_write(157,0);
	gpio_write(157,1);
}
int main(void)
{
	gpio_open(157,1);
	reset_atmega();
//--------Vytvor server a pripoj-----------------------------
  	int port_int = open_serial("/dev/ttyO2",B115200); 
  	printf("Serial port open - /dev/ttyO2\n");
 	int clientsock = vytvor_server(1213);
	int zap = 1;
//-----------------------------------------------------------
	char data_prijem[40][char_for_array];   //pole pre prijem dat 
	char data_odosli[40][char_for_array];   //pole pre odosielanie
	char prijem_serial[128];
while(zap){
//-------mazanie polii---------------------------------------
        for(int o=0;o<sizeof(data_prijem)/sizeof(data_prijem[0]);o++){
                memset(&data_prijem[o], 0, sizeof(data_prijem[o]));
	}
        for(int o=0;o<sizeof(data_odosli)/sizeof(data_odosli[0]);o++){
                memset(&data_odosli[o], 0, sizeof(data_odosli[o]));
	}
        memset(&prijem_serial, 0, sizeof(prijem_serial));

//-----------------------------------------------------
	gafuso_recv_array(clientsock, data_prijem,10);     //data zo socketu
//-----------------------------------------------------------
	if (strcmp(data_prijem[0], "data") == 0){
		//control string
		write_serial(port_int,data_prijem[0]);
		write_serial(port_int,"\n");
		//------------------
		int pocet_dat = atoi(data_prijem[1]); //load number of data
		read(port_int, prijem_serial,pocet_dat+10); // read data from serial
		for(int o=0;o!=pocet_dat;o++)	sprintf(data_odosli[o],"%d",prijem_serial[o]); //convert from byte to string
		gafuso_send_array(clientsock,data_odosli,pocet_dat);	//send data by gafuso protocol
	}
        else if(strcmp(data_prijem[0],"reset") == 0){
                reset_atmega();
	}
	else {
                write_serial(port_int,data_prijem[0]);
                write_serial(port_int,"\n");
		for(int o=1;o!=atoi(data_prijem[1]);o++){
			write_serial(port_int,data_prijem[o+1]);
			write_serial(port_int,"\n");
		}
	}
//---------------------------------------------------
	}
	close(clientsock);
	gpio_close(157);
	return 0;
}

