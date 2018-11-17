#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main()
{
	int network_socket;
	network_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(network_socket==-1)
	{
		printf("[-] Error in creating the socket.\n");
		return 0;
	}

	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9003);
	server_address.sin_addr.s_addr=INADDR_ANY;

	char client_response[200];
	int response_descriptor;
	printf("[!] Enter a string: \n");
	response_descriptor=read(0,client_response,sizeof(client_response));
	sendto(network_socket,client_response,response_descriptor,0,(struct sockaddr*)&server_address,sizeof(server_address));

	int recv_stat;
	int addr_len=sizeof(server_address);
	char server_response[200];
	recv_stat=recvfrom(network_socket,server_response,sizeof(server_response),0,(struct sockaddr*)&server_address,&addr_len);
	write(1,server_response,recv_stat);
	printf("[+] Successfully received.\n");
	
	close(network_socket);
	return 0;
}

