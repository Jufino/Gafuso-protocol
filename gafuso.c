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
  	if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)	quit("socket() failed");
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
//----------------------------------------------------------------
void send_data(int socket, char len[]){
	send(socket, len, strlen(len), 0);
}
//----------------------------------------------------------------
void GafusoSendImg(int socket, IplImage *img,int kvalita){
        vector<unsigned char> buff;
	vector<int> param = vector<int>(2);
      	param[0] = CV_IMWRITE_JPEG_QUALITY;
      	param[1] = kvalita;        
	Mat M = Mat(img);
        imencode(".jpg", M, buff, param);
	char len[10];
	sprintf(len, "%.8d", buff.size());
	send(socket,len,8,0);
  	send(socket, &buff[0], buff.size(), 0);
        buff.clear();
}
//-----------------------------------------------------------------
char *gafuso_send_buffer;
char *gafuso_recv_buffer;
unsigned long int size_send_buffer=0;
unsigned long int size_recv_buffer=0;
//--------------------------------------------------------------------
void GafusoAdd(char *data_to_add){
	char *size = (char*)malloc(sizeof(char)*8); 
	char *data_gafuso_add = (char*)realloc (gafuso_send_buffer, (size_send_buffer + strlen(data_to_add)+8) * sizeof(char));
	sprintf(size,"%.7d",strlen(data_to_add));	
	for(int x=0;x<strlen(size);x++)				*(data_gafuso_add + size_send_buffer++)= *(size + x);
	for(int x=0;x<(sizeof(data_to_add)/sizeof(char));x++)	*(data_gafuso_add + size_send_buffer++)= *(data_to_add + x);
	gafuso_send_buffer = data_gafuso_add;
}
//--------------------------------------------------------------------
void GafusoSend(int socket){
	char *size = (char*)malloc(sizeof(char)*11);
	sprintf(size,"%.10d",size_send_buffer);
	send_data(socket,size);
	send_data(socket,gafuso_send_buffer);
	size_send_buffer = 0;
	gafuso_send_buffer = NULL;
}
//--------------------------------------------------------------------
void GafusoRecv(int socket){
	char *size = (char*)malloc(10*sizeof(char)) ;
	recv(socket,size,10,0);
	size_recv_buffer = 0; 
	gafuso_recv_buffer = NULL;
	gafuso_recv_buffer = (char*) malloc(atoi(size)*sizeof(char));
	recv(socket,gafuso_recv_buffer,atoi(size),0);
}
//--------------------------------------------------------------------
char *GafusoLoadFirst(void){
        char *size = (char*)malloc(sizeof(char)*8);
	size_recv_buffer=0;
        for(unsigned char i=0;i<7;i++)	*(size+i)= *(gafuso_recv_buffer+size_recv_buffer++);
        char *data_from_recv = (char*)malloc(sizeof(char)*9);
        data_from_recv = (char*)malloc(sizeof(char)*(atoi(size)+1));
	int x = 0;
        for(int i=size_recv_buffer;i<(size_recv_buffer+atoi(size));i++)	*(data_from_recv+x++) = *(gafuso_recv_buffer+i);
        size_recv_buffer+=atoi(size);
	*(data_from_recv+x) = '\0';
        return &data_from_recv[0];
}
//--------------------------------------------------------------------
char *GafusoLoad(void){
	char *size = (char*)malloc(sizeof(char)*8);
        size_recv_buffer=0;
        for(unsigned char i=0;i<7;i++)  *(size+i)= *(gafuso_recv_buffer+size_recv_buffer++);
        char *data_from_recv = (char*)malloc(sizeof(char)*9);
        data_from_recv = (char*)malloc(sizeof(char)*(atoi(size)+1));
        int x = 0;
        for(int i=size_recv_buffer;i<(size_recv_buffer+atoi(size));i++) *(data_from_recv+x++) = *(gafuso_recv_buffer+i);
        size_recv_buffer+=atoi(size);
        *(data_from_recv+x) = '\0';
        return &data_from_recv[0];
}
//--------------------------------------------------------------------
