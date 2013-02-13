#include "libsocket.h"  
//----------------------------------------------------------
char * gafuso_send_buffer;
unsigned long int size_send_buffer=0;
void add_to_gafuso(char *data_to_add){
	int x;
	char *size = (char*)malloc(sizeof(char)*11);
	char *data_gafuso_add = (char*) realloc (gafuso_send_buffer, size_send_buffer + strlen(data_to_add) * sizeof(char) + 2);
	sprintf(size,"%.7d",strlen(data_to_add));	
	for(x=0;x<strlen(data_to_add);x++){
        	*(data_gafuso_add + size_send_buffer)= *(size + x);
        	size_recv_buffer++;
        }
	for(x=0;x<strlen(data_to_add);x++){	
		*(data_gafuso_add + size_send_buffer)= *(data_to_add + x);
		size_recv_buffer++;
	}
	*(data_gafuso_add + size_send_buffer) = '\0';
	gafuso_send_buffer = data_gafuso_add;
	free(data_gafuso_add);
	free(size);
}
void delete_from_gafuso(){
	i=0;
	free(data_gafuso);
}
void send_from_gafuso(int socket){
	char *size = (char*)malloc(sizeof(char)*11);
	sprintf(size,"%.10d",size_send_buffer);
	send_data(socket,size_send_buffer);
	send_data(socket,gafuso_send_buffer);
}

char *gafuso_recv_buffer;
unsigned long int size_recv_buffer=0;
void receive_from_gafuso(int socket){
	char *size = (char*)malloc(sizeof(char)*9);
	recv(socket,size,8,0);
	gafuso_recv_buffer = (char*) malloc(atoi(size));
	recv(socket,gafuso_recv_buffer,atoi(size),0);
	free(size);
}
void gafuso_from_start(char* data_from_recv){
        char *size = (char*)malloc(sizeof(char)*9);
	size_recv_buffer=0;
        for(unsigned char i=0;i<8;i++)  *(size+i)= *(gafuso_recv_buffer+i+size_recv_buffer);
        size_recv_buffer+=8;
        data_from_recv = (char*)malloc(sizeof(char)*atoi(size));
        int x = 0;
        for(int i=size_recv_buffer;i<(size_recv_buffer+atoi(size));i++){
                *(data_from_recv+x) = *(gafuso_recv_buffer+i)
        }

}
void data_from_recv(char* data_from_recv){
	char *size = (char*)malloc(sizeof(char)*9);
	for(unsigned char i=0;i<8;i++)	*(size+i)= *(gafuso_recv_buffer+i+size_recv_buffer);
	size_recv_buffer+=8;
	data_from_recv = (char*)malloc(sizeof(char)*atoi(size));
	int x = 0;
	for(int i=size_recv_buffer;i<(size_recv_buffer+atoi(size));i++)	*(data_from_recv+x) = *(gafuso_recv_buffer+i)
}


void quit(char* msg){
	fprintf(stderr,"%s\n", msg);
	exit(1);
}
//------------------------------------------------------------------
int vytvor_server(int PORT){
  	int clientsock,serversock;
  	struct sockaddr_in server;
  	struct timeval tv;	
  	if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {             
		quit("socket() failed");
	}    	
	/* setup server's IP and port */                                        
	memset(&server, 0, sizeof(server));                                     
	server.sin_family = AF_INET;                                            
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;                                    
                       
	if (bind(serversock, (struct sockaddr *)&server, sizeof(server)) == -1) {     
		quit("bind() failed");                                       
	}     
	
	/* wait for connection */                                               
	if (listen(serversock, 10) == -1) {                                     
		quit("listen() failed.");                                    
	}                                                                       

	printf("Waiting for connection on port %d\n", PORT);

	/* accept a client */                                                   
	if ((clientsock = accept(serversock, NULL, NULL)) == -1) {              
		quit("accept() failed");                                     
	}
	printf("Connection open on port %d\n", PORT);
	//nastavuje timeout 
//        tv.tv_sec = 0;
//        tv.tv_usec = recv_timeout*1000;
//        setsockopt(clientsock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,  sizeof tv);
	//-----------------
	return clientsock;
}
//--------------------------------------------------------------------------
int connect(char hostname[],int PORT){
	int sd;
	struct sockaddr_in pin;
	struct hostent *hp;
	struct timeval tv;
	/*skusi vyhladat hostovaci server */
	if ((hp = gethostbyname(hostname)) == 0) {
		perror("gethostbyname");
		exit(1);
	}

	/* zbera informacie o serveri */
	memset(&pin, 0, sizeof(pin));
	pin.sin_family = AF_INET;
	pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	pin.sin_port = htons(PORT);

	/* grab an Internet domain socket */
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* pripoj sa na host na porte */
	if (connect(sd,(struct sockaddr *)  &pin, sizeof(pin)) == -1) {
		perror("connect");
		exit(1);
	}
	//nastavuje timeout
 //       tv.tv_sec = 0;
 //       tv.tv_usec = recv_timeout*1000;
 //       setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,  sizeof tv);
	//----------------------------------
  	return sd;
}
//----------------------------------------------------------------
void send_data(int socket, char len[])
{
	send(socket, len, strlen(len), 0);
}
//----------------------------------------------------------------
void send_img(int socket, IplImage *img,int kvalita)
{
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
int gafuso_recv_array(int socket, char prijem[][char_for_array],unsigned int size){

  	char recvdata[size*char_for_array+size+1];
	recv(socket, recvdata,(size*char_for_array+size), 0);
	if(errno != EAGAIN){
		return gafuso_decode(prijem,recvdata);
	}
	else{
		return (-1);
	}
}
//-----------------------------------------------------------------
void gafuso_send_array(int socket, char odosli[][char_for_array],unsigned int size){
	char data_vystup[size*char_for_array+size+1];
	gafuso_code(data_vystup,odosli,size);
	send_data(socket,data_vystup);
}
//-----------------------------------------------------------------
