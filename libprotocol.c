#include "libprotocol.h"
//-----------------------------------------------------------
unsigned int gafuso_code(char data_vystup[],char (*data_vstup)[char_for_array],unsigned int size){
	unsigned int posun = 0;
	data_vystup[posun] = size;
	posun++;
	for(unsigned int i=0;i < size;i++){
		data_vystup[posun] = strlen(data_vstup[i]);
		posun++;
		for(unsigned int z=0;z<strlen(data_vstup[i]);z++){
			data_vystup[posun] = data_vstup[i][z];
			posun++;
		}
	}
	return posun;
}
//-----------------------------------------------------------
int gafuso_decode(char (*data_vystup)[char_for_array],char data_vstup[]){
	unsigned int posun=1;
	unsigned int size=1;
	int poc_dat=data_vstup[0];
	for(unsigned int i=0;i < data_vstup[0];i++){
		unsigned int poc_znakov=data_vstup[posun];
		size+=poc_znakov;
		if (size <= strlen(data_vstup)){
			posun++;
			for(unsigned int z=0;z<poc_znakov;z++){
				data_vystup[i][z] = data_vstup[posun];
				posun++;
			}
		}
		else{	
			poc_dat = -1;
			break;
		}
	}
	return poc_dat;
}
