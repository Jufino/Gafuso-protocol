#include "libprotocol.h"
//-----------------------------------------------------------
int gafuso_code(char data_vystup[],char (*data_vstup)[char_for_array],int size){
	int posun = 0;
	int poc_char_pocitadlo=0;		
	int byte_for_char = 1;
	int byte_for_dat = 1;
        for (int o=8; size > pow(2,o); o+=8) byte_for_dat=o/8;
	for (int o=8; char_for_array > pow(2, o); o+=8) byte_for_char=o/8;
	data_vystup[posun] = byte_for_dat;
	data_vystup[posun+1] = byte_for_char;
	posun+=2;
	for (int o=0;o!=byte_for_dat;o++){
		data_vystup[posun] = (size>>poc_char_pocitadlo)&0xFF;
		poc_char_pocitadlo+=8;
		posun++;
	}
	for(int i=0;i < size;i++){
		poc_char_pocitadlo=0;		
		for (int o=0;o!=byte_for_char;o++){
			data_vystup[posun] = (strlen(data_vstup[i])>>poc_char_pocitadlo)&0xFF;
			poc_char_pocitadlo+=8;
			posun++;
		}
		for(int z=0;z!= strlen(data_vstup[i]);z++){
			data_vystup[posun] = data_vstup[i][z];
			posun++;
		}
	}
	return posun;
}
//-----------------------------------------------------------
int gafuso_decode(char (*data_vystup)[char_for_array],char data_vstup[]){
	int posun=0;
	int size=0;
	int poc_znakov=0;
	int poc_char_pocitadlo=0;
	int byte_for_dat = data_vstup[posun];
	int byte_for_char = data_vstup[posun+1];
	posun+=2;
	for (int o=0;o!=byte_for_dat;o++){
		size+=(data_vstup[posun]<<poc_char_pocitadlo);
		poc_char_pocitadlo+=8;
		posun++;
	}
	for(int i=0;i != size;i++){
		poc_znakov=0;
		poc_char_pocitadlo=0;
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
	return posun;
}
//--------------------------------------------
