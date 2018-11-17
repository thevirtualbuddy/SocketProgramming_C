#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

int main()
{
	char client_response[200];
	int palindrome_status=0;	

	int server_socket;
	server_socket=socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int bind_status;
	bind_status = bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	if(bind_status == -1)
		printf("[-] Error in binding.\n");
	else
		printf("[+] Successfully binded.\n");
	while(1)
	{
		printf("\n[!] Listening for connection...");
		int listen_status = listen(server_socket,5);
		if(listen_status == -1)	
			printf("[-] Error in listening for connection.\n");
		int client_socket;
		client_socket = accept(server_socket,NULL,NULL);
		recv(client_socket,&client_response,sizeof(client_response),0);
		time_t t1;
	
		time(&t1);
		char*p;
		p=ctime(&t1);
		char server_response[100];
		int xxx;
		for(xxx=0;p[xxx]!='\0';xxx++)
		server_response[xxx]=p[xxx];
		server_response[xxx]='\0';		
		send(client_socket,&server_response,sizeof(server_response),0);
		close(client_socket);		
	}
	
	close(server_socket);	
	

	return 0;
}
