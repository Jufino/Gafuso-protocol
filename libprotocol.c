#include "libprotocol.h"
//-----------------------------------------------------------
int zakoduj(char data_vystup[],char (*data_vstup)[char_for_array],int size){
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
	return posun;
}
//-----------------------------------------------------------
int dekoduj(char (*data_vystup)[char_for_array],char data_vstup[]){
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
	return posun;
}
//--------------------------------------------
