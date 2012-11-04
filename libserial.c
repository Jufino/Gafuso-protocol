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
	//raw input and output
	my_termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	my_termios.c_oflag &= ~OPOST;
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
//-----------------------------------------
