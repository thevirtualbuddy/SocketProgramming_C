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
	
	struct sockaddr_in network_address;
	bzero(&network_address,sizeof(network_address));
	network_address.sin_family = AF_INET;
	network_address.sin_port = htons(9030);
	network_address.sin_addr.s_addr = INADDR_ANY;

	int connect_status = connect(network_socket,(struct sockaddr*)&network_address,sizeof(network_address));
	if(connect_status == -1)
	{
		printf("[-] Error in connecting to the remote server.\n");
		return 0;
	}
	else
		printf("[+] Successfully connected to the remote server.\n");
	char destuffed_response[100],stuffed_response[100],check;
	printf("[!] Enter your message: ");
	scanf("%s",destuffed_response);
	int i,j;
	for(i=0,j=0;destuffed_response[i]!='\0';i++,j++)
	{
		check = destuffed_response[i];
		if(check =='@' || check == '#')
		{
			stuffed_response[j] = '#';
			j++;
			stuffed_response[j] = destuffed_response[i];
		}
		stuffed_response[j]=destuffed_response[i];
	}
	stuffed_response[j]='\0';
	printf("[+] The message after the stuffing is: %s\n",stuffed_response);
	int send_stat = send(network_socket,stuffed_response,sizeof(stuffed_response),0);
	if(send_stat == -1)
		printf("[-] Error in sending.\n");
	else
		printf("[+] Successfully sent to server.\n");

	char server_response[100];
	int recv_stat = recv(network_socket,server_response,sizeof(server_response),0);
	printf("The destuffed message is: %s\n",server_response);

	close(network_socket);
	return 0;
}
