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

	network_socket=socket(AF_INET,SOCK_STREAM,0);

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

	int listen_status;
	listen_status=listen(network_socket,5);
	if(listen_status==-1)
		printf("\n[-] Error in listening.\n");
	else
	{
		while(1)
		{
			printf("\n[+] Listening for connection...\n");

			int client_socket;

			client_socket=accept(network_socket,NULL,NULL);
			if(client_socket==-1)
				printf("[-] Error in accepting...\n");
			else
				printf("[+] Client successfully accepted.\n");

			char response[200];

			int recv_status;
			recv_status=recv(client_socket,response,sizeof(response),0);
			if(recv_status==-1)
				printf("[-] Error in receiving.\n");
			else
				printf("[+] Message successfully received from client.\n");

			printf("[+] The response from the client is:\n");

			write(1,response,recv_status);

			printf("[+] Sending back the message...\n");
			int send_status;
			send_status=send(client_socket,response,recv_status,0);
			if(send_status==-1)
				printf("[-] Error in sending back the response.\n");
			else
				printf("[+] Response echoed back successfully\n");
			close(client_socket);
		}


	}
	close(network_socket);
	return 0;
}
