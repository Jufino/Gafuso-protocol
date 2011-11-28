#ifndef _LIBPROTOCOL_H
#define _LIBPROTOCOL_H
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
int zakoduj(char data_vystup[],char (*data_vstup)[char_for_array],int size);
//-----------------------------------------------------------
//data_vystup je multiarray = vystupne rozkodovane data
//data_vstup je char = zakodovane data v klastrovom protokole
//-----------------------------------------------------------
int dekoduj(char (*data_vystup)[char_for_array],char data_vstup[]);
//--------------------------------------------
#endif
