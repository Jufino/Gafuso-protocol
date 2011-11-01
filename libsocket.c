#include "libsocket.h"  
//----------------------------------------------------------
void quit(char* msg,int retval){
	fprintf(stderr,"%s\n", msg);
	exit(retval);
}
//------------------------------------------------------------------
int vytvor_server(int PORT){
  int clientsock,serversock;
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
	return clientsock;
}
//--------------------------------------------------------------------------
int connect(char hostname[],int PORT){
	int	sd;
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	struct hostent *hp;

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
  	send(socket, &buff[0], buff.size(), 0);
        buff.clear();
}
//-----------------------------------------------------------------
void gafuso_get_socket(int socket, char prijem[][char_for_array]){
  	char recvdata[1000000];
	recv(socket, recvdata, 1000000, 0);
	gafuso_decode(prijem,recvdata);
}
//-----------------------------------------------------------------
void gafuso_send_socket(int socket, char odosli[][char_for_array],int pocet_dat)
{
	char data_vystup[100000];
	gafuso_code(data_vystup,odosli,pocet_dat);
	send_data(socket,data_vystup);
}
//-----------------------------------------------------------------
