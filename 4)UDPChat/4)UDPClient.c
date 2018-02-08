#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/socket.h>

void communicateServer(int clientSocket,struct sockaddr_in serverAddress){
	char send_buffer[1024];
	char receive_buffer[1024];
	
	while(1){
		bzero(send_buffer,1024);
		printf("Enter the message for server \n");
		fgets(send_buffer,1024,stdin);
		sendto(clientSocket,send_buffer,sizeof(send_buffer),0,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
		
		bzero(receive_buffer,1024);
		recvfrom(clientSocket,receive_buffer,sizeof(receive_buffer),0,NULL,NULL);
		printf("Message from server \n");
		printf("%s \n",receive_buffer);

		
		if(strncmp(receive_buffer,"exit",4)==0)
			break;
		
		
	}
}


void main(){

	int clientSocket;

	char buffer[100];
	struct sockaddr_in serverAddress;

	clientSocket = socket(AF_INET,SOCK_DGRAM,0);

	if(clientSocket == -1)
		printf("Socket creation failed \n");
	else{
		printf("Socket creation successful \n");

		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(9000);
		serverAddress.sin_addr.s_addr = INADDR_ANY;

		communicateServer(clientSocket,serverAddress);

		/*int serverAddressLength = sizeof(serverAddress);

		sendto(clientSocket,"Hello Server",13,0,(struct sockaddr *)&serverAddress,serverAddressLength);

		printf("test \n");

		int res = recvfrom(clientSocket,buffer,sizeof(buffer),0,NULL,NULL);

		printf("%s \n",buffer);*/

	}

}