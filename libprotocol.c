#include "libprotocol.h"
//-----------------------------------------------------------
int gafuso_code(char data_vystup[],char (*data_vstup)[char_for_array],int size){
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
	int posun=0;
	int size=0;
	int poc_znakov=0;
	size=data_vstup[posun];
	posun++;
//	printf("size = %d\n",size);
	if(size < sizeof(data_vstup)/sizeof(char)){
		for(int i=0;i < size;i++){
			poc_znakov=data_vstup[posun];
			posun++;
//			printf("poc_znakov %d,%d\n",i,poc_znakov);
			for(int z=0;z<poc_znakov;z++){
				data_vystup[i][z] = data_vstup[posun];
				posun++;
			}
		}
		return size;
	}
	else	return -1;

}
