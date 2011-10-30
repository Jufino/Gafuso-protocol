#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls
#include <errno.h>
#include <stdio.h>
//--------------------------------------------------------
//otvara seriovy port
//--------------------------------------------------------
int port_int;
int open_serial(const char *port, speed_t speed) {
    int fd;
   fd = open(port, O_RDWR);
    if (fd < 0)
    {
        printf("open error %d %s\n", errno, strerror(errno));
    }
    else
    {
        struct termios my_termios;
        tcgetattr(fd, &my_termios);
	//nastavenie portu
    	cfsetispeed(&my_termios, speed);
    	cfsetospeed(&my_termios, speed);
	my_termios.c_cflag |= (CLOCAL | CREAD);
	my_termios.c_cflag &= ~PARENB;
	my_termios.c_cflag &= ~CSTOPB;
	my_termios.c_cflag &= ~CSIZE;
	my_termios.c_cflag |= CS8;
	my_termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	my_termios.c_iflag &= ~(IXON | IXOFF | IXANY);
	//-----------------------------------
	tcsetattr(fd, TCSANOW, &my_termios);
    }
    return fd;
}
void close_serial(int port){
  close(port);
}
void write_serial(int port,char data[]){ 
  write(port,data,strlen(data));
}

//-----------------------------------------------------------
//byte_for_dat_serial -definuje max pocet dat ktore mozu byt prenesene ak nieje definovane
//nastavi sa na 1
//#define byte_for_dat_serial 1 = pocet dat = 2 na (byte_for_dat_serial*8)
//-----------------------------------------------------------
#ifndef byte_for_dat_serial
#define byte_for_dat_serial 1
#endif 
//-----------------------------------------------------------
//byte_for_char_serial -definuje max pocet znakov v jednotlivych datach ktore mozu byt prenesene 
//ak nieje definovane nastavi sa na 1
//#define byte_for_char_serial 1 = pocet znakov = 2 na (byte_for_char_serial*8)
//-----------------------------------------------------------
#ifndef byte_for_char_serial
  #define byte_for_char_serial 1
#endif 
//-----------------------------------------------------------
//char_for_array 10  - max pocet znakov vo vystupe
//#define char_for_array 10
//-----------------------------------------------------------
#ifndef char_for_array_serial
  #define char_for_array_serial 10
#endif 
//funkcia zakoduje data do klastroveho protokolu, data_vystup = tu su zakodovane data, data_vstup=je to 
//vstup vo forme multiarray, size = velkost pola
//zakoduj(datay,arr,sizeof(arr)/sizeof(arr[0]));	//zakoduje arr do datay = data na odosielanie
//-----------------------------------------------------------
void zakoduj_serial(char data_vystup[],char (*data_vstup)[char_for_array_serial],int size){
	int posun = 0;
//urcuje pocet dat-----------------------
	int poc_char_pocitadlo=0;		
	for (int o=0;o!=byte_for_dat_serial;o++){
		data_vystup[posun] = (size>>poc_char_pocitadlo)&0xFF;
		poc_char_pocitadlo+=8;
		posun++;
	}
//----------------------------------------
	for(int i=0;i < size;i++){
//pocet znakov v nasledujucom data------------------
		poc_char_pocitadlo=0;		
		for (int o=0;o!=byte_for_char_serial;o++){
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
	data_vystup[posun] = '\n';
}
//-----------------------------------------------------------
//-----------------------------------------------------------
//data_vystup je multiarray = vystupne rozkodovane data
//data_vstup je char = zakodovane data v klastrovom protokole
//-----------------------------------------------------------
void dekoduj_serial(char (*data_vystup)[char_for_array_serial],char data_vstup[]){
	int posun=0;
	int size=0;
	int poc_znakov=0;
	int poc_char_pocitadlo=0;
//nacita pocet dat--------------------
	for (int o=0;o!=byte_for_dat_serial;o++){
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
		for (int o=0;o!=byte_for_char_serial;o++){
			poc_znakov+=((data_vstup[posun])<<poc_char_pocitadlo);
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
//------------------------------------------
//odosiela znaky v poli na seriovy port
//------------------------------------------
void send_data_serial(char (*data_vstup)[char_for_array_serial],int pocet_dat){
  char odosli[128];
  for (int o=0;o<sizeof(odosli)/sizeof(odosli[0]);o++){
    memset(&odosli[o], 0, sizeof(odosli[o])); 
  }  
  zakoduj_serial(odosli,data_vstup,pocet_dat);
  write_serial(port_int,odosli);   
}
//------------------------------------------
//prijma znaky zo serioveho portu do pola
//------------------------------------------
void receive_data_serial(char (*prijem)[char_for_array_serial]){
  char prijem_data[128];
  memset(&prijem_data, 0, sizeof(prijem_data));  
  read(port_int,&prijem_data,128);
  printf(prijem_data);
  dekoduj_serial(prijem,prijem_data);
}
//------------------------------------------
