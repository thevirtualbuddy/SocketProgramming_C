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

	struct sockaddr_in network_address;
	bzero(&network_address,sizeof(network_address));
	network_address.sin_family = AF_INET;
	network_address.sin_port = htons(9010);
	network_address.sin_addr.s_addr = INADDR_ANY;

	int connect_status = connect(network_socket , (struct sockaddr*)&network_address, sizeof(network_address));
	if(connect_status == -1)
	{
		printf("[-] Error in connectiong to the remote server.\n");
		return 0;
	}
	else
		printf("[+] Successfully connected to the remote server.\n");

	char check,destuffed_response[100],stuffed_response[100];
	printf("[!] Enter your message to be stuffed: ");
	scanf("%s",destuffed_response);

	int i,j,count;
	for(i=0,j=0;destuffed_response[i]!='\0';i++,j++)
	{
		check = destuffed_response[i];
		if(check == '1')
			count++;
		else
			count  = 0;
		if(count == 6)
		{
			stuffed_response[j++]='0';
			count = 0;

		}
		stuffed_response[j] = destuffed_response[i];
	}
	stuffed_response[j]='\0';
	printf("[+] The response after stuffing is %s\n",stuffed_response);
	int send_status = send(network_socket,stuffed_response,sizeof(stuffed_response),0);
	if(send_status == -1)
		printf("[-] Error in sending the data.\n");
	else
		printf("[+] Successfully sent to the server.\n");
	printf("\n[!!] Waiting for the server to respond.\n");
	char server_response[100];
	int recv_stat = recv(network_socket,server_response,sizeof(server_response),0);
	printf("The response from the server is : %s\n",server_response);
	//write(1,server_response,recv_stat);
	close (network_socket);
	return 0;
}
