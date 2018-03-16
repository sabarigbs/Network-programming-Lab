#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void main(){
	
	int SocketFd;

	//Create socket
	SocketFd = socket(AF_INET,SOCK_STREAM,0);

	if(SocketFd ==  -1)
		printf("Socket creation failed \n");
	else
		printf("Socket creation successful and socket id is %d\n",SocketFd);

}