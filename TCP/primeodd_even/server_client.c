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
	network_address.sin_port=htons(9033);
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
			
			if(translated_response==2)
			{
				int status;
				status=htonl(3000);				
				int send_status;				
				send_status=send(client_socket,&status,sizeof(status),0);
				if(send_status==-1)
					printf("[-] Error in sending.\n");
				else
					printf("[+] Successfully responded to the client.\n");
			}
			if(translated_response%2==0)
			{
				int even_status;
				even_status=htonl(10000);				
				int send_status;				
				send_status=send(client_socket,&even_status,sizeof(even_status),0);
				if(send_status==-1)
					printf("[-] Error in sending.\n");
				else
					printf("[+] Successfully responded to the client.\n");

			}
			else
			{
				int network_socket2;

				network_socket2=socket(AF_INET,SOCK_STREAM,0);
	
				struct sockaddr_in network_address2;
				bzero(&network_address2,sizeof(network_address2));
				network_address2.sin_family=AF_INET;
				network_address2.sin_port=htons(9043);
				network_address2.sin_addr.s_addr=INADDR_ANY;

				int connect_status2;

				connect_status2=connect(network_socket2,(struct sockaddr*)&network_address2,sizeof(network_address2));
				if(connect_status2==-1)
				{	
					printf("\n[-] Error in connecting to the remote server.\n");
					return 0;
				}

				else
				{
					printf("[+] Successfully connected to the remote server2.\n");
					int msg2,client_msg2,server_msg2,recv_status2,recv_translated2;
					

					client_msg2=htonl(translated_response);
					int send_status2=send(network_socket2,&client_msg2,sizeof(client_msg2),0);
					if(send_status2==-1)
					{
						printf("[-] Error on sending the data.\n");
						return 0;
					}

					else
					{
						recv_status2=recv(network_socket2,&server_msg2,sizeof(server_msg2),0);
						if(recv_status2==-1)
							printf("[-] Error in receiving.\n");
						else
						{
							recv_translated2=htonl(server_msg2);

							if(recv_translated2==2000)
								printf("[+] Number is a prime.\n");
							else	
								printf("[+] Number is odd.\n");
						
				
							int send_status,status;
							status=htonl(recv_translated2);				
							send_status=send(client_socket,&status,sizeof(status),0);
							if(send_status==-1)
								printf("[-] Error in sending.\n");
							else
								printf("[+] Successfully responded to the client.\n");		
						}
						
					}


	}

	close (network_socket2);
			}
			
			
			close (client_socket);

		}
	}

	close (network_socket);
	return 0;
}
