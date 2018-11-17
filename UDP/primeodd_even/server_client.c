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
	network_socket=socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in network_address;
	bzero(&network_address,sizeof(network_address));
	network_address.sin_family=AF_INET;
	network_address.sin_port=htons(9033);
	network_address.sin_addr.s_addr=INADDR_ANY;

	int addr_len=sizeof(network_address);
	
	int bind_status=bind(network_socket,(struct sockaddr*)&network_address,sizeof(network_address));
	if(bind_status==-1)
		printf("[-] Error in binding\n");
	else
		printf("[+] Successfully binded.\n");
	
	while(1)
	{
		printf("\n[+] Listening for connections...\n");

			
		int client_response, response_stat, translated_response;

		response_stat=recvfrom(network_socket,&client_response,sizeof(client_response),0,(struct sockaddr*)&network_address,&addr_len);
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
			send_status=sendto(network_socket,&status,sizeof(status),0,(struct sockaddr*)&network_address,sizeof(network_address));
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
			send_status=sendto(network_socket,&even_status,sizeof(even_status),0,(struct sockaddr*)&network_address,sizeof(network_address));
			if(send_status==-1)
				printf("[-] Error in sending.\n");
			else
				printf("[+] Successfully responded to the client.\n");

		}
		else
		{
			int network_socket2;
			network_socket2=socket(AF_INET,SOCK_DGRAM,0);
	
			struct sockaddr_in network_address2;
			bzero(&network_address2,sizeof(network_address2));
			network_address2.sin_family=AF_INET;
			network_address2.sin_port=htons(9043);
			network_address2.sin_addr.s_addr=INADDR_ANY;
			
			int addr_len2=sizeof(network_address2);
			int msg2, client_msg2, server_msg2, recv_status2, recv_translated2;
					

			client_msg2=htonl(translated_response);
			int send_status2=sendto(network_socket2,&client_msg2,sizeof(client_msg2),0,(struct sockaddr*)&network_address2,sizeof(network_address2));
			if(send_status2==-1)
			{
				printf("[-] Error on sending the data.\n");
				return 0;
			}
			else
			{
				recv_status2=recvfrom(network_socket2,&server_msg2,sizeof(server_msg2),0,(struct sockaddr*)&network_address2,&addr_len2);
				if(recv_status2==-1)
					printf("[-] Error in receiving.\n");
				else
				{
					recv_translated2=htonl(server_msg2);

					if(recv_translated2==2000)
						printf("[+] Number is a prime.\n");
					if(recv_translated2==3000)
						printf("[+] Number is even prime.\n");
						
				
					int send_status,status;
					status=htonl(recv_translated2);				
					send_status=sendto(network_socket,&status,sizeof(status),0,(struct sockaddr*)&network_address,sizeof(network_address));
					if(send_status==-1)
						printf("[-] Error in sending.\n");
					else
						printf("[+] Successfully responded to the client.\n");		
				}
					
			}
			close(network_socket2);

		}

	}
		

	close (network_socket);
	return 0;
}
