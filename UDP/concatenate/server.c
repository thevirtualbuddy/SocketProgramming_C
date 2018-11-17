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

	network_socket=socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in server_address;
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9003);
	server_address.sin_addr.s_addr=INADDR_ANY;

	int bindstatus;
	bindstatus=bind(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	if(bindstatus==-1)
	{
		printf("\n[-] Error in binding.\n");
		return 0;
	}
	else
		printf("\n[+] Binding success!\n");

	while(1)
		{
			printf("\n[+] Listening for connection...\n");


			char response[200];
			int addr_len=sizeof(server_address);

			int recv_status;
			recv_status=recvfrom(network_socket,response,sizeof(response),0,(struct sockaddr*)&server_address,&addr_len);
			if(recv_status==-1)
				printf("[-] Error in receiving.\n");
			else
				printf("[+] Message successfully received from client 1.\n");

			printf("[+] The response from the client 1 is:\n");

			write(1,response,recv_status);
			response[recv_status]='\0';		
			
			printf("\n[+] Listening for connection 2...\n");


			int response1;

			int recv_status1;
			recv_status1=recvfrom(network_socket,&response1,sizeof(response1),0,(struct sockaddr*)&server_address,&addr_len);
			if(recv_status1==-1)
				printf("[-] Error in receiving.\n");
			else
				printf("[+] Message successfully received from client 2.\n");

			int num=htonl(response1);
			printf("[+] The response from the client 2 is: %d\n",num);
			


			
			char client2msg[20];

			sprintf(client2msg,"%d",num);

			strcat(response,client2msg);

			printf("[+] Sending back the message...\n");
			int send_status;
			send_status=sendto(network_socket,response,sizeof(response),0,(struct sockaddr*)&server_address,addr_len);
			if(send_status==-1)
				printf("[-] Error in sending back the response.\n");
			else
				printf("[+] Response echoed back successfully\n");
			int send_status1;
			send_status1=sendto(network_socket,response,sizeof(response),0,(struct sockaddr*)&server_address,addr_len);
			if(send_status==-1)
				printf("[-] Error in sending back the response.\n");
			else
				printf("[+] Response echoed back successfully\n");
			
	}


	
	close(network_socket);
	return 0;
}
