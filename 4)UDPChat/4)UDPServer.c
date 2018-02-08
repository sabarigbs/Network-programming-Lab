#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

void communicateClient(int connectionSocket,struct sockaddr_in clientAddress){
	
	char receive_buffer[1024];
	char send_buffer[1024];

	int clientAddressLength = sizeof(clientAddress);

	while(1){
		bzero(receive_buffer,1024);
		recvfrom(connectionSocket,receive_buffer,sizeof(receive_buffer),0,(struct sockaddr *)&clientAddress,&clientAddressLength);
		printf("Message from client \n");
		printf("%s \n",receive_buffer);
		
		bzero(send_buffer,1024);
		printf("Enter the message for client \n");
		fgets(send_buffer,1024,stdin);
		sendto(connectionSocket,send_buffer,sizeof(send_buffer),0,(struct sockaddr *)&clientAddress,sizeof(clientAddress));
		
		if(strncmp(send_buffer,"exit",4)==0)
			break;

	}

}


void main(){

	int serverSocket;

	int bindResult;

	char buffer[100];

	serverSocket = socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in serverAddress,clientAddress;

	if(serverSocket == -1)
		printf("Socket is not created \n");
	else{
		printf("Socket created successfully \n");

		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(9000);
		serverAddress.sin_addr.s_addr = INADDR_ANY;

		bindResult = bind(serverSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress));

		if(bindResult == -1)
			printf("Bind not successful \n");
		else{
			printf("Bind successful \n");

			communicateClient(serverSocket,clientAddress);

			/*recvfrom(serverSocket,buffer,sizeof(buffer),0,(struct sockaddr *)&clientAddress,&clientAddressLength);

			printf("%s \n ",buffer);

			sendto(serverSocket,buffer,sizeof(buffer),0,(struct sockaddr *)&clientAddress,sizeof(clientAddress));*/
		}

	}
}