#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in network_address;
	bzero(&network_address,sizeof(network_address));
	network_address.sin_family=AF_INET;
	network_address.sin_port=htons(9003);
	network_address.sin_addr.s_addr=INADDR_ANY;
	
	int connect_status;
	connect_status=connect(network_socket,(struct sockaddr*)&network_address,sizeof(network_address));
	if(connect_status==-1)
	{
		printf("\n[-] Error in connecting to the remote server.\n");
		return 0;
	}
	else
		printf("[+] Successfully connected to the remote server.\n");

	
		char client_response[200];
		printf("\n[!] Waiting for server to respond...\n");
		
		char server_response[200];
		int recv_status=recv(network_socket,server_response,sizeof(server_response),0);
		
		printf("\n[+] The server echoed the following:\n");
		write(1,server_response,recv_status);

	
		close(network_socket);
	
	return 0;

}
