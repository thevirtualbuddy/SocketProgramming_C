#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int prime_check(int num)
{
	int prime_status;
	if(num<2)
	{
		prime_status=1000;
	}
	else
	{
		prime_status=2000;
		for(int i=2;i<=num/2;i++)
		{
			if(num%i==0)
			{
				prime_status = 1000;
				break;
			}
		}
	}

	return prime_status;
}

int main()
{
	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in network_address;
	bzero(&network_address,sizeof(network_address));
	network_address.sin_family=AF_INET;
	network_address.sin_port=htons(9043);
	network_address.sin_addr.s_addr=INADDR_ANY;

	int bind_status=bind(network_socket,(struct sockaddr*)&network_address,sizeof(network_address));
	if(bind_status==-1)
		printf("[-] Error in binding\n");
	else
		printf("[+] Successfully binded.\n");
	
	int listen_status;
	listen_status=listen(network_socket,5);
	if(listen_status==-1)
		printf("\n[-] Error in listening for connections.\n");
	else
	{
		while(1)
		{
			printf("\n[+] Listening for connections...\n");

			int client_socket;
			client_socket=accept(network_socket,NULL,NULL);
			if(client_socket==-1)
				printf("\n[-] Error in accepting the client connection.\n");
			else
				printf("[+] Successfully accepted the client's connection.\n");

			
			int client_response, response_stat, translated_response;

			response_stat=recv(client_socket,&client_response,sizeof(client_response),0);
			if(response_stat==-1)
				printf("[-] Error in receiving.\n");
			else
				printf("[+] Response successfully received.\n");
			
			translated_response=htonl(client_response);

			int prime_status1,prime_status;
			prime_status1=prime_check(translated_response);
			prime_status=htonl(prime_status1);
			int send_status;

			send_status=send(client_socket,&prime_status,sizeof(prime_status),0);
			if(send_status==-1)
				printf("[-] Error in sending.\n");
			else
				printf("[+] Successfully responded to the client.\n");

			close (client_socket);

		}
	}

	close (network_socket);
	return 0;
}
