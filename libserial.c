#include "libserial.h"
//--------------------------------------------------------
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
	my_termios.c_cflag |= (CLOCAL | CREAD | CRTSCTS);
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
void close_serial(int port){
	close(port);
}
//-----------------------------------------
void write_serial(int port,char data[]){ 
	write(port,data,strlen(data));
}
//------------------------------------------
void send_data_serial(int port, char (*data_vstup)[char_for_array_serial],int pocet_dat){
  	char odosli[128];
  	int pocet_datx=0;
    	memset(&odosli, 0, sizeof(odosli));   
 	pocet_datx = zakoduj(odosli,data_vstup,pocet_dat);
  	odosli[pocet_datx] = '\n';  
	write_serial(port,odosli);   
}
//------------------------------------------
void receive_data_serial(int port, char (*prijem)[char_for_array_serial]){
  	char prijem_data[128];
  	memset(&prijem_data, 0, sizeof(prijem_data));  
  	read(port,&prijem_data,128);
  	dekoduj(prijem,prijem_data);
}
//------------------------------------------
