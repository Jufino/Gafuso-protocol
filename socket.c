//Socket
#include <netinet/in.h>                                                         
#include <sys/socket.h>                                                         
#include <arpa/inet.h>  
//-----------------------------------------------------------
//operacie z datami a
//-----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
//-----------------------------------------------------------
//byte_for_dat -definuje max pocet dat ktore mozu byt prenesene ak nieje definovane
//nastavi sa na 1
//#define byte_for_dat 1 = pocet dat = 2 na (byte_for_dat*8)
//-----------------------------------------------------------
#ifndef byte_for_dat
#define byte_for_dat 1
#endif 
//-----------------------------------------------------------
//byte_for_char -definuje max pocet znakov v jednotlivych datach ktore mozu byt prenesene 
//ak nieje definovane nastavi sa na 1
//#define byte_for_char 1 = pocet znakov = 2 na (byte_for_char*8)
//-----------------------------------------------------------
#ifndef byte_for_char
  #define byte_for_char 1
#endif 
//-----------------------------------------------------------
//char_for_array 10  - max pocet znakov vo vystupe
//#define char_for_array 10
//-----------------------------------------------------------
#ifndef char_for_array
  #define char_for_array 10
#endif 
//-----------------------------------------------------------
//definicia portu pri otvoreni socketu
//#define PORT 1212
//-----------------------------------------------------------
#ifndef PORT
  #define PORT 1212
#endif 
//-----------------------------------------------------------
int serversock, clientsock; 
//-----------------------------------------------------------
//funkcia zakoduje data do klastroveho protokolu, data_vystup = tu su zakodovane data, data_vstup=je to 
//vstup vo forme multiarray, size = velkost pola
//zakoduj(datay,arr,sizeof(arr)/sizeof(arr[0]));	//zakoduje arr do datay = data na odosielanie
//-----------------------------------------------------------
void zakoduj(char data_vystup[],char (*data_vstup)[char_for_array],int size){
	int posun = 0;
//urcuje pocet dat-----------------------
	int poc_char_pocitadlo=0;		
	for (int o=0;o!=byte_for_dat;o++){
		data_vystup[posun] = (size>>poc_char_pocitadlo)&0xFF;
		poc_char_pocitadlo+=8;
		posun++;
	}
//----------------------------------------
	for(int i=0;i < size;i++){
//pocet znakov v nasledujucom data------------------
		poc_char_pocitadlo=0;		
		for (int o=0;o!=byte_for_char;o++){
			data_vystup[posun] = (strlen(data_vstup[i])>>poc_char_pocitadlo)&0xFF;
			poc_char_pocitadlo+=8;
			posun++;
		}
//vkladanie data do znakov--------------------------
		for(int z=0;z!= strlen(data_vstup[i]);z++){
			data_vystup[posun] = data_vstup[i][z];	//vlozi hodnotu znaku
			posun++;
		}
//--------------------------------------------------
	}
}
//-----------------------------------------------------------
//data_vystup je multiarray = vystupne rozkodovane data
//data_vstup je char = zakodovane data v klastrovom protokole
//-----------------------------------------------------------
void dekoduj(char (*data_vystup)[char_for_array],char data_vstup[]){
	int posun=0;
	int size=0;
	int poc_znakov=0;
	int poc_char_pocitadlo=0;
//nacita pocet dat--------------------
	for (int o=0;o!=byte_for_dat;o++){
		size+=(data_vstup[posun]<<poc_char_pocitadlo);
		poc_char_pocitadlo+=8;
		posun++;
	}
//------------------------------------
	for(int i=0;i != size;i++){
//------------------------------------
		poc_znakov=0;
		poc_char_pocitadlo=0;
//nacita pocet znakov v nasledujucom data
		for (int o=0;o!=byte_for_char;o++){
			poc_znakov+=(data_vstup[posun]<<poc_char_pocitadlo);
			poc_char_pocitadlo+=8;
			posun++;
		}
//prijma znaky----------------------
		for(int z=0;z!= poc_znakov;z++){
			data_vystup[i][z] = data_vstup[posun];
			posun++;
		}
//------------------------------------------
	}
}
//--------------------------------------------
void quit(char* msg, int retval)
{
	fprintf(stderr, "%s\n", msg);
	exit(retval);
}
//--------------------------------------------

//--------------------------------------------
//vytvori server
//-----------------------------------------------------------------
void vytvor_server()
{
  struct sockaddr_in server;	
  if ((serversock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {             
		quit("socket() failed", 1);
	}    	
	/* setup server's IP and port */                                        
	memset(&server, 0, sizeof(server));                                     
	server.sin_family = AF_INET;                                            
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;                                    
                       

	if (bind(serversock, (struct sockaddr *)&server, sizeof(server)) == -1) {     
		quit("bind() failed", 1);                                       
	}     
	
	/* wait for connection */                                               
	if (listen(serversock, 10) == -1) {                                     
		quit("listen() failed.", 1);                                    
	}                                                                       

	printf("Waiting for connection on port %d\n", PORT);

	/* accept a client */                                                   
	if ((clientsock = accept(serversock, NULL, NULL)) == -1) {              
		quit("accept() failed", 1);                                     
	}
  printf("Connection open on port 1213\n"); 
}
//----------------------------------------------------------------
//odosle char array cez socket
//----------------------------------------------------------------
void send_data(int socket, char len[])
{
	send(socket, len, strlen(len), 0);
}
//-----------------------------------------------------------------
//nacita zo data zo socketu
//-----------------------------------------------------------------
void get_data_socket(char prijem[][char_for_array]){
	char buffer[5];
	recv(clientsock, buffer, 5, 0);
	char recvdata[atoi(buffer)];
  recv(clientsock, recvdata, atoi(buffer), 0);
	dekoduj(prijem,recvdata);
}
//-----------------------------------------------------------------
void send_data_socket(char odosli[][char_for_array],int pocet_dat)
{
  char data_vystup[128];
  zakoduj(data_vystup,odosli,pocet_dat);
  send_data(clientsock,data_vystup);
}