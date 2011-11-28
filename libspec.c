#include "libspec.h"
//-----------------------------------------------------------
//precita text ulozeny do pola
//-----------------------------------------------------------
void precitaj_text(char text[]){
	char sys_text[strlen(text)+20];
	memset(&sys_text[0], 0, sizeof(sys_text));       
//-----------------------------------------------------------
	strcpy (sys_text,"espeak -vsk '\''");                          
	strcat (sys_text,text);
	strcat (sys_text,"'\''");
	system(sys_text);
}
//----------------------------------------------------------
/*void reset_atmega(){
	GPIO_open(157,1);
	GPIO_write(157,0);
	GPIO_write(157,1);
	GPIO_close(157);
}*/
