#include "libsocket.h"  
//----------------------------------------------------------
int serversock,clientsock;
void quit(char* msg,int retval){
	fprintf(stderr,"%s\n", msg);
	exit(retval);
}
//------------------------------------------------------------------
void vytvor_server(){
  struct sockaddr_in server;	
  if ((serversock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {             
		quit("socket() failed", 1);
	}    	
	/* setup server's IP and port */                                        
	memset(&server, 0, sizeof(server));                                     
	server.sin_family = AF_INET;                                            
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;                                    
                       

	if (bind(serversock, (struct sockaddr *)&server, sizeof(server)) == -1) {     
		quit("bind() failed", 1);                                       
	}     
	
	/* wait for connection */                                               
	if (listen(serversock, 10) == -1) {                                     
		quit("listen() failed.", 1);                                    
	}                                                                       

	printf("Waiting for connection on port %d\n", PORT);

	/* accept a client */                                                   
	if ((clientsock = accept(serversock, NULL, NULL)) == -1) {              
		quit("accept() failed", 1);                                     
	}
	printf("Connection open on port %d\n", PORT); 
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
  	send(socket, &buff[0], buff.size(), 0);
        buff.clear();
}
//-----------------------------------------------------------------
void get_data_socket(char prijem[][char_for_array]){
	char buffer[5];
	recv(clientsock, buffer, 5, 0);
	char recvdata[atoi(buffer)];
  	recv(clientsock, recvdata, atoi(buffer), 0);
	dekoduj(prijem,recvdata);
}
//-----------------------------------------------------------------
void send_data_socket(char odosli[][char_for_array],int pocet_dat)
{
	char data_vystup[100000];
	zakoduj(data_vystup,odosli,pocet_dat);
	send_data(clientsock,data_vystup);
}
//-----------------------------------------------------------------
