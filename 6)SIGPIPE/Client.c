#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>


void sig_pipe(){
	printf("Server terminated prematurely \n");
	exit(0);
}

void communicateServer(int clientSocket){
	char send_buffer[1024];
	char receive_buffer[1024];
	
	while(1){
		bzero(send_buffer,1024);
		printf("Enter the message for server \n");
		fgets(send_buffer,1024,stdin);
		write(clientSocket,send_buffer,sizeof(send_buffer));
		
		bzero(receive_buffer,1024);
		read(clientSocket,receive_buffer,sizeof(receive_buffer));
		printf("Message from server \n");
		printf("%s \n",receive_buffer);

		
		/*if(strncmp(receive_buffer,"exit",4)==0)
			break;*/
		
		
	}
}

void main(){

	int  clientSocket,connectionResult;

	struct sockaddr_in serverAddress;

	//Create a socket
	clientSocket = socket(AF_INET,SOCK_STREAM,0);

	if(clientSocket == -1 )
		printf("Socket creation failed \n");
	else
		printf("Socket creation successful \n");

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8000);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	signal(SIGPIPE,sig_pipe);

	//Connect with server 
	connectionResult = connect(clientSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress));

	if(connectionResult == -1 )
		printf("Connection failed \n");
	else{
		printf("Connection scuccessful \n");
		communicateServer(clientSocket);
		//close(clientSocket);
	}



}
