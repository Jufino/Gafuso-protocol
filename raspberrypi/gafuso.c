#include "gafuso.h"
//----------------------------------------------------------
void quit(char* msg){
	fprintf(stderr,"%s\n", msg);
	exit(1);
}
//------------------------------------------------------------------
int GafusoCreate(int PORT){
  	int clientsock,serversock;
  	struct sockaddr_in server;	
	if ((serversock = socket(AF_INET, SOCK_STREAM,0)) == -1)     quit("socket() failed");
	memset(&server, 0, sizeof(server));                                     
	server.sin_family = AF_INET;                                            
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;                                         	
	if (bind(serversock, (struct sockaddr *)&server, sizeof(server)) == -1)	quit("bind() failed");            
	if (listen(serversock, 10) == -1) 					quit("listen() failed.");
	printf("Gafuso wait at port %d\n", PORT);                           	
	if ((clientsock = accept(serversock, NULL, NULL)) == -1) 		quit("accept() failed");
	printf("Gafuso connect at port %d\n", PORT);
	return clientsock;
}
//--------------------------------------------------------------------------
int GafusoConnect(char hostname[],int PORT){
	int sd;
	struct sockaddr_in pin;
	struct hostent *hp;
	if ((hp = gethostbyname(hostname)) == 0)			quit("gethostbyname");
	memset(&pin, 0, sizeof(pin));
	pin.sin_family = AF_INET;
	pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	pin.sin_port = htons(PORT);
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)		quit("socket");
	if (connect(sd,(struct sockaddr *)  &pin, sizeof(pin)) == -1) 	quit("connect");
  	return sd;
}
//--------------------------------------------------------------------------
void GafusoClose(int PORT){
	close(PORT);
}
//-----------------------------------------------------------------
char *gafuso_send_buffer;
char *gafuso_recv_buffer;
unsigned long int size_send_buffer=0;
unsigned long int size_recv_buffer=0;
//--------------------------------------------------------------------
void GafusoAdd(char data_to_add[],int length){
	char size[8];
	char *data_gafuso_add;
	if (size_send_buffer == 0)	data_gafuso_add = (char*)malloc((length+7)*sizeof(char));
	else				data_gafuso_add = (char*)realloc (gafuso_send_buffer,(length+7+size_send_buffer)*sizeof(char));
	sprintf(size,"%.7d",length);	     
	for(int x=0;x<strlen(size);x++)		*(data_gafuso_add + size_send_buffer++)= *(size + x);
	for(int x=0;x<length;x++)		*(data_gafuso_add + size_send_buffer++)= *(data_to_add + x);
	gafuso_send_buffer = data_gafuso_add;
}
//--------------------------------------------------------------------
void GafusoSend(int socket){
	char size[12];
	sprintf(size,"%.10d",size_send_buffer);
	char buffer_send[size_send_buffer+10];	
	sprintf(buffer_send,"%s%s",size,gafuso_send_buffer);
  send(socket, buffer_send, size_send_buffer+10, 0);
}
//--------------------------------------------------------------------
void GafusoBuffDel(){
	size_send_buffer = 0;
	gafuso_send_buffer=NULL;
}
//--------------------------------------------------------------------
void GafusoRecv(int socket){
	char size[10];
	recv(socket,size,10,0);
	gafuso_recv_buffer= NULL;
	gafuso_recv_buffer=(char*)malloc(sizeof(char)*atoi(size));
	size_recv_buffer = 0; 
	recv(socket,gafuso_recv_buffer,atoi(size),0);
}
//--------------------------------------------------------------------
char *GafusoLoad(char mode){
        char size[8];
        if (mode == 'f')        size_recv_buffer=0;
        for(unsigned char i=0;i<7;i++)  size[i] = *(gafuso_recv_buffer+size_recv_buffer++);
        size[7] = '\0';
	int SizeInt = atoi(size);
        char *data_from_recv = (char*)malloc((SizeInt+1)*sizeof(char));
        for(int i=0;i<SizeInt;i++)      *(data_from_recv+i) = *(gafuso_recv_buffer+(size_recv_buffer++));
        *(data_from_recv+SizeInt) = '\0';
        return data_from_recv;
}
//-------------------------------------------------------------------
