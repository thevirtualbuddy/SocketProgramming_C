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
	


	int addr_len=sizeof(network_address);
		char client_response[200];
		printf("\n[!] Enter your message:\n");
		int msg = read(0,client_response,sizeof(client_response));
		int send_status=sendto(network_socket,client_response,msg,0,(struct sockaddr*)&network_address,addr_len);
		if(send_status==-1)
			printf("\n[-] Error in sending.\n");
		else
			printf("\n[+] Message successfully sent to server.\n");
		printf("\n[!] Waiting for server to respond...\n");
		
		char server_response[200];
		int recv_status=recvfrom(network_socket,server_response,sizeof(server_response),0,(struct sockaddr*)&network_address,&addr_len);
		
		printf("\n[+] The server echoed the following:\n");
		//write(1,server_response,recv_status);
		printf("%s\n",server_response);
	
		close(network_socket);
	
	return 0;

}
