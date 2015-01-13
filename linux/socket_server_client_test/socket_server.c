/*This is a Linux edition */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int socket_server,socket_client;
	struct sockaddr_in sockaddr_server, sockaddr_client;
	int ret_val = 0;
	char buffer[46] = {0};
	char data[4096] = {0};

	sockaddr_server.sin_family = AF_INET;
	sockaddr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr_server.sin_port = htons(60000);

	socket_server = socket(AF_INET,SOCK_STREAM,0);
	if(socket_server < 0){
		perror("socket");
		return errno;
	}

	ret_val = bind(socket_server,(struct sockaddr *)&sockaddr_server,
		sizeof(sockaddr_server));
	if(ret_val != 0){
		perror("bind");
		return errno;
	}

	ret_val = listen(socket_server,10);
	if(ret_val != 0){
		perror("listen");
		return errno;
	}
	while(1){
		ret_val = sizeof(sockaddr_client);
		socket_client = accept(socket_server,(struct sockaddr*)&sockaddr_client,&ret_val);
		printf("addr:%s:%d\n",inet_ntop(AF_INET,&sockaddr_client.sin_addr,buffer,46),ntohs(sockaddr_client.sin_port));
		ret_val = recv(socket_client,data,4096,0);
		data[ret_val] = '\0';;
		printf("recv: %s\n",data);
	}
	close(socket_server);
	close(socket_client);

	return 0;
}

