#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void communicateServer(int clientSocket){
	
	char *buff = (char *)malloc(sizeof(char));
	printf("Enter the filename \n");
	fgets(buff,255,stdin);
	write(clientSocket,buff,sizeof(buff));
	read(clientSocket,buff,sizeof(buff));

	printf("Reply from server \n %s",buff);
}


void main(){

	int  clientSocket,connectionResult;

	struct sockaddr_in serverAddress;

	//Create a socket
	clientSocket = socket(AF_INET,SOCK_STREAM,0);

	if(clientSocket == -1 )
		printf("Socket creation failed \n");
	else{
		printf("Socket creation successful \n");
	

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8000);
	serverAddress.sin_addr.s_addr = INADDR_ANY;


	//Connect with server 
	connectionResult = connect(clientSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress));

	if(connectionResult == -1 )
		printf("Connection failed \n");
	else{
		printf("Connection scuccessful \n");
		communicateServer(clientSocket);
		close(clientSocket);
	}
}


}