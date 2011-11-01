#ifndef _LIBPROTOCOL_H
#define _LIBPROTOCOL_H
//-----------------------------------------------------------
//operacie z datami a
//-----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <math.h>
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
int gafuso_code(char data_vystup[],char (*data_vstup)[char_for_array],int size);
//-----------------------------------------------------------
//data_vystup je multiarray = vystupne rozkodovane data
//data_vstup je char = zakodovane data v klastrovom protokole
//-----------------------------------------------------------
int gafuso_decode(char (*data_vystup)[char_for_array],char data_vstup[]);
//--------------------------------------------
#endif
