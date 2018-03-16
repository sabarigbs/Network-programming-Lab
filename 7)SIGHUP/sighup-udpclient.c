#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	char msg[100]="",msg1[100]="";
	int sockfd,confd;
	struct sockaddr_in server,client;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
	{
		printf("socket error correction\n");
	}
	printf("socket created successfully\n");
	bzero(&server,sizeof(server));
	server.sin_port=htons(3230);
	server.sin_family=AF_INET;
	inet_aton("127.0.0.1",&server.sin_addr);
	int len=sizeof(server);
while(1)
{
		printf("enter the msg\n");
		gets(msg);
		sendto(sockfd,(char *)msg,strlen(msg),0,(struct sockaddr *)&server,len);
		recvfrom(sockfd,(char *)msg,100,0,(struct sockaddr *)&server,&len);
		printf("msg from the client is %s",msg);
}
	close(sockfd);
}

