#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int network_socket;

	network_socket=socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in server_address;
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9003);
	server_address.sin_addr.s_addr=INADDR_ANY;

	int bindstatus;
	bindstatus=bind(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	if(bindstatus==-1)
	{
		printf("\n[-] Error in binding.\n");
		return 0;
	}
	else
		printf("\n[+] Binding success!\n");

	while(1)
	{
		printf("\n[+] Listening for connection...\n");
		char client_response;
		int recv_status,addr_len;
		addr_len=sizeof(server_address);

		recv_status=recvfrom(network_socket,&client_response,sizeof(client_response),0,(struct sockaddr*)&server_address,&addr_len);
	
		if(client_response=='y')
		{	
		char* response[]={"Hello World\n","IT Department\n","School of Tech\n","NEHU\n","Computer Network\n","Socket Programming\n"};

		int send_status;
		int a = rand()%5;
		int sizeofmessage=strlen(response[a]);
		send_status=sendto(network_socket,response[a],sizeofmessage,0,(struct sockaddr*)&server_address,sizeof(server_address));
		if(send_status==-1)
			printf("[-] Error in sending back the response.\n");
		else
			printf("[+] Response echoed back successfully\n");
	
		}
	}


	close(network_socket);
	return 0;
}
