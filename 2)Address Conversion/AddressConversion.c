#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){

	struct in_addr ipAddress;
	long int address;
	char *ptr;
	char *hostAddress = (char *)malloc(sizeof(char));

	printf("Enter the host Address \n");
	fgets(hostAddress,100,stdin);

	address = inet_addr(hostAddress);

	printf("%s in binary form is %ld \n",hostAddress,address);

	ipAddress.s_addr = address;

	ptr = inet_ntoa(ipAddress);

	printf("Converting binary address back to host address %s\n",ptr);

	return 0;
}