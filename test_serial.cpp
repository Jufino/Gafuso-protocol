#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#define char_for_array_serial 10
#include "libprotocol.c";
#include "libtime.c";
#include "libserial.c";

//--------------------------------------------

int main(void)
{
//--------Vytvor server a pripoj-----------------------------
int  port_int = open_serial("/dev/ttyO2",B115200); 
printf("Serial port open - /dev/ttyO2\n");
printf("DTR OFF\n");  
reset_Atmega(port_int);
printf("DTR OK\n");
//-----------------------------------------------------------
while(1);
/*while(1){
	char prijemx[2][10];
	memset(&prijemx[0], 0, sizeof(prijemx[0]));
	memset(&prijemx[1], 0, sizeof(prijemx[1]));
	sprintf(prijemx[0],"%s","data");
	sprintf(prijemx[1],"%s","100");  
//	write_serial(port_int,"ahoj\n");
	send_data_serial(port_int,prijemx,2);  
	char prijem_data[15];
  	int i=0;
	memset(&prijem_data, 0, sizeof(prijem_data));  
	i = read(port_int,&prijem_data,128);
	//receive_data_serial(prijem_data);
//	printf("Data senzor 8 : %x\n",prijem_data[8]);
//	printf("Data senzor 9 : %x\n",prijem_data[9]);
//	printf("Data kompas : %d\n",prijem_data[8]+(prijem_data[9]<<8));
	printf("%d\n",prijem_data[0]);
	msleep(50);
  }
//------------------------------  -----------------------------
*/	
return 0;
}
