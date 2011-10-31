//-----------------------------------------------------------
//operacie z datami a
//-----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
//-----------------------------------------------------------
//byte_for_dat -definuje max pocet dat ktore mozu byt prenesene ak nieje definovane
//nastavi sa na 1
//#define byte_for_dat 1 = pocet dat = 2 na (byte_for_dat*8)
//-----------------------------------------------------------
#ifndef byte_for_dat
#define byte_for_dat 1
#endif 
//-----------------------------------------------------------
//byte_for_char -definuje max pocet znakov v jednotlivych datach ktore mozu byt prenesene 
//ak nieje definovane nastavi sa na 1
//#define byte_for_char 1 = pocet znakov = 2 na (byte_for_char*8)
//-----------------------------------------------------------
#ifndef byte_for_char
  #define byte_for_char 1
#endif 
//-----------------------------------------------------------
//char_for_array 10  - max pocet znakov vo vystupe
//#define char_for_array 10
//-----------------------------------------------------------
#ifndef char_for_array
  #define char_for_array 10
#endif 
//-----------------------------------------------------------
//funkcia zakoduje data do klastroveho protokolu, data_vystup = tu su zakodovane data, data_vstup=je to 
//vstup vo forme multiarray, size = velkost pola
//zakoduj(datay,arr,sizeof(arr)/sizeof(arr[0]));	//zakoduje arr do datay = data na odosielanie
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
//data_vystup je multiarray = vystupne rozkodovane data
//data_vstup je char = zakodovane data v klastrovom protokole
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
