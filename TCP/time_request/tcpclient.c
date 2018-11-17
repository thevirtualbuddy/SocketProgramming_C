#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int connection_status = connect(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	if(connection_status==-1)
		printf("[-] Error in connecting to the server!\n");
	else
		printf("\n[+] Successfully connected to the remote server.");
	
	char client_message[200];
	printf("\n[$] Type 'yes' to receive the time: ");
	scanf("%s",client_message);
	
	send(network_socket,client_message,sizeof(client_message),0);

	char server_response[100];
	recv(network_socket,server_response,sizeof(server_response),0);
	printf("\n%s\n",server_response);	
	
	
	close(network_socket);
	return 0;
	
	
}
