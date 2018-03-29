#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<errno.h>

void communicateClient(int connectionSocket){
	
	char *buff = (char *)malloc(100);
	int file;
	char *filename = (char *)malloc(sizeof(char));
	


	read(connectionSocket,buff,sizeof(buff));
	int len = strlen(buff);
	
	int i=0;
	for(i=0;i<len;i++)
		filename[i]=buff[i];
	filename[i]='\0';
	

	printf("Filename %s \n",filename);
	

	file = open(filename,O_RDONLY);
	//printf("%d \n",file);
	if(file <= 0){
	 printf("File couldn't be opened with error %s  \n",strerror(errno)); 
	 strcpy(buff,"File couldn't be opened");
	}
	else
		read(file,buff,sizeof(buff));

	write(connectionSocket,buff,sizeof(buff));

}

void main(){
	
	int serverSocket,connectionSocket,clientAddressLength;

	int bind_result,listen_result;

	struct sockaddr_in serverAddress,clientAddress;

	//Create socket
	serverSocket = socket(AF_INET,SOCK_STREAM,0);

	if(serverSocket ==  -1)
		printf("Socket creation failed \n");
	else{
		printf("Socket creation successful \n");
	

		//Configure server address
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(8000);
		serverAddress.sin_addr.s_addr = INADDR_ANY;


		//Binds the created socket with the given address
		bind_result = bind(serverSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress));

		if(bind_result == -1)
			printf("Bind process failed \n");
		else{
			printf("Bind successful \n");
		

			//Listens for client connection on the specified socket
			listen_result = listen(serverSocket,10);    //10 is the backlog value that specifies maximum number of clients can wait in the connection queue

			if(listen_result == -1 )
				printf("Server is not listening \n");
			else{
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
		}

   }



}
