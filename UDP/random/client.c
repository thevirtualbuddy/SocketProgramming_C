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
	network_socket=socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in network_address;
	bzero(&network_address,sizeof(network_address));
	network_address.sin_family=AF_INET;
	network_address.sin_port=htons(9003);
	network_address.sin_addr.s_addr=INADDR_ANY;
	

	char client_response;
	int client_res_des;
	printf("\n[!] Type 'y' and press enter to initialize the process...\n");
	scanf("%c",&client_response);
	//client_res_des=read(0,client_response,sizeof(client_response));

	int send_stat;
	send_stat=sendto(network_socket,&client_response,sizeof(client_response),0,(struct sockaddr*)&network_address,sizeof(network_address));
	char server_response[200];
	int addr_len=sizeof(network_address);
	int recv_status=recvfrom(network_socket,server_response,sizeof(server_response),0,(struct sockaddr*)&network_address,&addr_len);
		
	printf("\n[+] The server echoed the following:\n");
	write(1,server_response,recv_status);

	
	close(network_socket);
	
	return 0;

}
