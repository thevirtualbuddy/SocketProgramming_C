#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int palindrome(char ch[],int end)
{
	int start=0;
	end=end-2;

	while(start<end)
	{
		if(ch[start]!=ch[end])
			return 0;
		else
		{
			start++;
			end--;
		}
	}
	
	return 1;
}

int main()
{
	int network_socket;
	network_socket=socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in server_address;
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9030);
	server_address.sin_addr.s_addr=INADDR_ANY;

	int bind_status;
	bind_status=bind(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	if(bind_status==-1)
	{
		printf("\n[-] Error in binding.\n");
		return 0;
	}	
	else
		printf("\n[+] Binding done.\n");

	int addr_len=sizeof(server_address);
	
	while(1)
	{
		printf("\n[+] Listening for connections.\n");
			
		char response[200];
		int recv_status;
		recv_status=recvfrom(network_socket,response,sizeof(response),0,(struct sockaddr*)&server_address,&addr_len);
		if(recv_status==-1)
			printf("[-] Error in receiving from the client.\n");
		else
			printf("[+] Successfully accepted.\n");

		printf("[+] The response from client is:\n");
		write(1,response,recv_status);

		int palin_status, server_response;
		palin_status=palindrome(response,recv_status);
			
		server_response=htonl(palin_status);
			
		int send_status;
		send_status=sendto(network_socket,&server_response,sizeof(server_response),0,(struct sockaddr*)&server_address,sizeof(server_address));
		if(send_status==-1)
			printf("[-] Error in sending.\n");
		else
			printf("[+] Successfully checked.\n");
	}

	close(network_socket);

	return 0;
}

