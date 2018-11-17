#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int network_socket = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_address;
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9030);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int bind_status = bind(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));
	if(bind_status == -1)
	{
		printf("[-] Error in binding.\n");
		return 0;
	}
	else
		printf("[-] Successfully binded.\n");
	int listen_status = listen(network_socket,5);
	if(listen_status == -1)
		printf("[-] Error in listening.\n");
	else
	{
		while(1)
		{
			printf("[+] Listening for connections..\n");
			int client_socket;
			client_socket = accept(network_socket,NULL,NULL);
			if(client_socket == -1)
				printf("[-] Error in accepting.\n");
			else
				printf("[+] Successfully accepted.\n");
			char stuffed_response[100],destuffed_response[100],check;
			int recv_stat = recv(client_socket,stuffed_response,sizeof(stuffed_response),0);
			if(recv_stat == -1)
				printf("[-] Error in receiving.\n");
			else
				printf("[+] The stuffed response from the client is : %s\n",stuffed_response);

			int i,j;
			for(i=0,j=0;stuffed_response[i]!='\0';i++,j++)
			{
				check = stuffed_response[i];
				if(check == '#')
				{
					i++;
					destuffed_response[j]=stuffed_response[i];
				}
				destuffed_response[j]=stuffed_response[i];
			}
			destuffed_response[j]='\0';
			printf("[+] The destuffed response to be sent is: %s\n",destuffed_response);
			int send_stat = send(client_socket,destuffed_response,sizeof(destuffed_response),0);
			if(send_stat== -1)
				printf("[-] Error in sending.");
			else
				printf("[+] Successfully sent.\n");
			close (client_socket);
		}
	}
	close(network_socket);
	return 0;
}
