#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>//close()
#include<netinet/in.h>//struct sockaddr_in
#include<arpa/inet.h>//inet_ntoa

#include "TCPClient.h"

void TCPClient_Process_Info(int s)
{
	
	int send_num;
	int recv_num;
	char send_buf[]="tigerjibo";
	char recv_buf[50];	
	while(1)
	{
		printf("\nBegin send\n");
		send_num = send(s,send_buf,sizeof(send_buf),0);
		if(send_num <0)
		{
			perror("send");
			exit(1);
		}
		else
		{
			printf("send success:%s\n",send_buf);
		}
		
		
	}
	
}

void maintest(void)
{
	int sock_fd;
	struct sockaddr_in addr_serv;	//Server address
	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd<0)
	{
		perror("sock");
		exit(1);
	}
	else
	{
		printf("sock successful\n");
	}
	
	memset(&addr_serv,0,sizeof(addr_serv));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_port = htons(DEST_PORT);
	addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDRESS);
	
	if(connect(sock_fd,(struct sockaddr*)&addr_serv,sizeof(struct sockaddr))<0)
	{
		perror("connect");
		printf("connect(%d)\n",errno);
		exit(1);
	}
	else
	{
		printf("connect successful\n");
	}
	
	TCPClient_Process_Info(sock_fd);
	close(sock_fd);
}

