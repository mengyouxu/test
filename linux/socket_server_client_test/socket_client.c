/*This is a Linux edition */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
	int socket_fd;
	struct sockaddr_in dest;//include <netinet/in.h>
	char buffer[1024];
	int ret_val = 0;
	socket_fd = socket(AF_INET,SOCK_STREAM,0);
	if(socket_fd <0 ){
		perror("socket");
		exit(errno);
	}

	memset(&dest,0,sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(60000);
	ret_val = inet_aton(argv[1],&dest.sin_addr.s_addr);
	if(ret_val == 0){
		perror(argv[1]);
		return errno;
	}
	ret_val = connect(socket_fd,(struct sockaddr*)&dest,sizeof(dest));
	if(ret_val != 0){
		perror("connect");
		return errno;
	}
	ret_val = send(socket_fd,argv[2],strlen(argv[2])+1,0);
	printf("send %d bytes\n",ret_val);
	ret_val = recv(socket_fd, buffer,1024,0);
	printf("recv %d bytes : %s\n",ret_val,buffer); 
	close(socket_fd);
	return 0;
}

