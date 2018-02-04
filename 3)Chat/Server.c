#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void communicateClient(int connectionSocket){
	
	char receive_buffer[1024];
	char send_buffer[1024];

	while(1){
		bzero(receive_buffer,1024);
		read(connectionSocket,receive_buffer,sizeof(receive_buffer));
		printf("Message from client \n");
		printf("%s \n",receive_buffer);
		
		bzero(send_buffer,1024);
		printf("Enter the message for client \n");
		fgets(send_buffer,1024,stdin);
		write(connectionSocket,send_buffer,sizeof(send_buffer));
		
		if(strncmp(send_buffer,"exit",4)==0)
			break;

	}

}

void main(){
	
	int serverSocket,connectionSocket,clientAddressLength;

	int bind_result,listen_result;

	struct sockaddr_in serverAddress,clientAddress;

	//Create socket
	serverSocket = socket(AF_INET,SOCK_STREAM,0);

	if(serverSocket ==  -1)
		printf("Socket creation failed \n");
	else
		printf("Socket creation successful \n");

	//Configure server address
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8000);
	serverAddress.sin_addr.s_addr = INADDR_ANY;


	//Binds the created socket with the given address
	bind_result = bind(serverSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress));

	if(bind_result == -1)
		printf("Bind process failed \n");
	else
		printf("Bind successful \n");

	//Listens for client connection on the specified socket
	listen_result = listen(serverSocket,10);    //10 is the backlog value that specifies maximum number of clients can wait in the connection queue

	if(listen_result == -1 )
		printf("Server is not listening \n");
	else
		printf("Server is listening \n"); 

	clientAddressLength = sizeof(clientAddress);
	
	connectionSocket = accept(serverSocket,(struct sockaddr *)&clientAddress,&clientAddressLength);

	if(connectionSocket == -1 )
		printf("New connection rejected \n");
	else{
		printf("New connection accepted \n");
		communicateClient(connectionSocket);
	}





}
