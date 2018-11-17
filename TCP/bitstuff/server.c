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
	network_socket = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_address;
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_port = htons(9010);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int bind_status = bind(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	if(bind_status==-1)
	{
		printf("[-]Error in binding.\n");
		return 0;
	}
	else
		printf("\n[+] Binding success.\n");

	int listen_status=listen(network_socket,5);
	if(listen_status==-1)
		printf("[-]Error in listening.\n");
	else
	{
		while(1)
		{
			printf("[+] Listening for connections.\n");
			int client_socket = accept(network_socket,NULL,NULL);
			if(client_socket == -1)
				printf("[-] Error in accepting the client.\n");
			else
				printf("[+] Client sucessfully accepted.\n");

			char stuffed_response[100];
			int recv_stat = recv(client_socket,stuffed_response,sizeof(stuffed_response),0);
			if(recv_stat == -1)
				printf("[-] Error in receiving.\n");
			else
				printf("[+] The stuffed response from client is : %s\n", stuffed_response);

			char check , destuffed_response[100];
			int k=0,i=0, count=0;
			for(i=0,k=0;i<recv_stat;i++)
			{
				destuffed_response[k++] = stuffed_response[i];
				check = stuffed_response[i];
				if(check == '1')
					count++;
				else
					count = 0;
				if(count == 5)
				{
					i=i+2;
					destuffed_response[k++]=stuffed_response[i];
					count =0;
				}
			}
			destuffed_response[k] ='\0';
			printf("[+]The destuffed response is %s\n",destuffed_response);
			
			int send_stat = send(client_socket, destuffed_response,sizeof(destuffed_response),0);
			if(send_stat == -1)
				printf("[-] Error in sending back the response.\n");
			else
				printf("[+] Responsed sent back successfully.\n");
			close (client_socket);
		}

	}
	return 0;
}
