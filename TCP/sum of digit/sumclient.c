#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
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

	int connect_status=connect(network_socket,(struct sockaddr*)&network_address,sizeof(network_address));
	if(connect_status==-1)
	{
		printf("[-] Error in connecting to the remote server.\n");
		return 0;
	}

	else
	{
		printf("\n[+] Successfully connected to the remote server.\n");

		int client_num;
		printf("Enter a number:\t");
		scanf("%d",&client_num);
		
		int num=htonl(client_num);
		int send_status=send(network_socket,&num,sizeof(num),0);
		if(send_status==-1)
			printf("[-] Error in sending the number.\n");
		else
		{
			printf("\n[+] Data sent successfully.\n");

			int server_response;
			int recv_status=recv(network_socket,&server_response,sizeof(server_response),0);
			if(recv_status==-1)
				printf("[-] Error in receiving from the server.\n");
			else
			{
				int server_num=htonl(server_response);
				printf("[+] The server responded the sum as: %d\n",server_num);
			}
		}

	}
	printf("\n[+] Closing the socket and exiting successfully.\n");
	close(network_socket);
	return 0;
}
