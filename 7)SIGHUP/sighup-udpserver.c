#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
int sockfd;
void myhand()
{
printf("SIGHUPcaught\n");
printf("restarting server\n");
close(sockfd);
execl("/udpserver","udpserver",NULL);
printf("Server is not restarted\n");
}
int main()
{
	char msg[100]="",rply[100]="";
	int len;
	struct sockaddr_in server,client;
	signal(SIGHUP,myhand);
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
		
	if(sockfd<0)
	{
		printf("socket error correction\n");
	}
	printf("socket created successsssssssssfully\n");
	bzero(&server,sizeof(server));
	server.sin_port=htons(3230);
	server.sin_family=AF_INET;
	inet_aton("127.0.0.1",&server.sin_addr);
	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))==0)
		while(1)
		{
			recvfrom(sockfd,(char *)msg,100,0,(struct sockaddr *)&client,&len);
			puts(msg);
			sendto(sockfd,(char *)rply,strlen(msg),0,(struct sockaddr *)&client,len);
		}
	close(sockfd);
}

