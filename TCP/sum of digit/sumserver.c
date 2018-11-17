#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	network_address.sin_port=htons(9010);
	network_address.sin_addr.s_addr=INADDR_ANY;

	int bind_status;
	bind_status=bind(network_socket,(struct sockaddr*)&network_address,sizeof(network_address));
	if(bind_status==-1)
	{
		printf("[-] Error in binding.\n");
		return 0;
	}
	else
		printf("\n[+] Successfully binded.\n");

	int listen_status=listen(network_socket,4);
	if(listen_status==-1)
		printf("[-] Error in listening for connection.\n");
	else
	{
		while(1)
		{
			printf("\n[+] Listening for connections...\n");

			int client_socket;
			client_socket=accept(network_socket,NULL,NULL);
			if(client_socket==-1)
				printf("[-] Error in accepting the network.\n");
			else
				printf("[+] Successfully accepted connection from the client.\n");


			int client_response,server_sum;
			int recv_desc;
			recv_desc=recv(client_socket,&client_response,sizeof(client_response),0);
			if(recv_desc==-1)
				printf("[-] Error in receiving.\n");
			else
			{	
				int client_num = htonl(client_response);
				printf("The number received from the client is: %d\n",client_num);

				int sum=0;
				while(client_num!=0)
				{
					sum+=client_num%10;
					client_num=client_num/10;
				}

				server_sum=htonl(sum);
				sum=0;
			}
		
			printf("[+] Sending the sum.\n");
			int send_status=send(client_socket,&server_sum,sizeof(int),0);
			if(send_status==-1)
				printf("[-] Error in sending back the data to client.\n");
			else
				printf("[+] Data sent back successfully to client.\n");
			close(client_socket);
		}
	}
	close(network_socket);
	return 0;
}
