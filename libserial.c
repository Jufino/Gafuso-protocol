#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls
#include <errno.h>
#include <stdio.h>
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
	//nastavenie rychlosti-----------------
    	cfsetispeed(&my_termios, speed);
    	cfsetospeed(&my_termios, speed);
	//-------------------------------------
	my_termios.c_cflag |= (CLOCAL | CREAD);
	//nieje parita,8N1
	my_termios.c_cflag &= ~PARENB;
	my_termios.c_cflag &= ~CSTOPB;
	my_termios.c_cflag &= ~CSIZE;
	my_termios.c_cflag |= CS8;
	//raw input
	my_termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	//nieje software
	my_termios.c_iflag &= ~(IXON | IXOFF | IXANY);
	//-----------------------------------
	tcsetattr(fd, TCSANOW, &my_termios);
    }
    return fd;
}
//-----------------------------------------
//uzatvara port
//-----------------------------------------
void close_serial(int port){
	close(port);
}
//-----------------------------------------
//zapis na port
//-----------------------------------------
void write_serial(int port,char data[]){ 
	write(port,data,strlen(data));
}
//------------------------------------------
//odosiela znaky v poli na seriovy port
//------------------------------------------

void send_data_serial(char (*data_vstup)[char_for_array_serial],int pocet_dat){
  	char odosli[128];
  	int pocet_datx=0;
    	memset(&odosli, 0, sizeof(odosli));   
 	pocet_datx = zakoduj(odosli,data_vstup,pocet_dat);
  	odosli[pocet_datx] = '\n';  
	write_serial(port_int,odosli);   
}
//------------------------------------------
//prijma znaky zo serioveho portu do pola
//------------------------------------------
void receive_data_serial(char (*prijem)[char_for_array_serial]){
  	char prijem_data[128];
  	memset(&prijem_data, 0, sizeof(prijem_data));  
  	read(port_int,&prijem_data,128);
  	dekoduj(prijem,prijem_data);
}
//------------------------------------------
