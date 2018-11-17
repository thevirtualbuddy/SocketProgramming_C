#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int main()
{
	int network_socket;
	network_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(network_socket==-1)
	{
		printf("Error in creating the socket.\n");
		return 0;
	}

	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9003);
	server_address.sin_addr.s_addr=INADDR_ANY;

	int bind_status;
	bind_status=bind(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	if(bind_status==-1)
	{
		printf("[-] Error in binding.\n");
		return 0;
	}
	
	int addr_len;
	addr_len=sizeof(server_address);

	while(1)
	{
		char* client_response[200];
		printf("[+] Waiting for connection...\n");

		int recv_stat;
		recv_stat=recvfrom(network_socket,client_response,sizeof(client_response),0,(struct sockaddr *)&server_address,&addr_len);
		printf("\nThe client message is:\n");
		write(1,client_response,recv_stat);
		
		int send_stat;
		send_stat=sendto(network_socket,client_response,recv_stat,0,(struct sockaddr*)&server_address,sizeof(server_address));
		if(send_stat!=-1)
			printf("[+] Message echoed back successfully.\n\n");
	}
	return 0;
}


