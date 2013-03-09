#ifndef _LIBSERIAL_H
#define _LIBSERIAL_H

#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
//--------------------------------------------------------
int SerialOpen(const char *port, speed_t speed);
//-----------------------------------------
void SerialClose(int port);
//-----------------------------------------
void SerialWrite(int port,char data[]);
//------------------------------------------
char *SerialReadLine(int port, int max);
//------------------------------------------
char *SerialRead(int port,int pocet);
#endif
