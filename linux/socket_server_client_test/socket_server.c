/*This is a Linux edition */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <db.h>

#include "client_info.h"

void db_print_err(int ret,int line)
{
	if(ret != 0){
		printf("L%d ERROR: %s\n",line,db_strerror(ret));
	}
}

int main(int argc, char *argv[])
{
	int socket_server,socket_client;
	struct sockaddr_in sockaddr_server, sockaddr_client;
	int ret_val = 0;
	char buffer[46] = {0};
	char data[4096] = {0};
	DB *dbp;
	DBT db_key, db_data;
	unsigned int flags = 0;
	struct client_info aclient_info;

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
	flags = DB_CREATE;
	ret_val = db_create(&dbp,NULL,0);
	db_print_err(ret_val,__LINE__);
	ret_val = dbp->open(dbp,NULL,"client_list.db",NULL,DB_HASH,flags,0);
	db_print_err(ret_val,__LINE__);

	while(1){
		ret_val = sizeof(sockaddr_client);
		socket_client = accept(socket_server,(struct sockaddr*)&sockaddr_client,&ret_val);
		memset(data,0,1024);
		ret_val = recv(socket_client,data,1024,0);
		
		memcpy(&aclient_info,data,256);
		memset(buffer,'\0',16);
		memset(&db_key,0,sizeof(DBT));
		memset(&db_data,0,sizeof(DBT));
		
		inet_ntop(AF_INET,&sockaddr_client.sin_addr,buffer,16);
		aclient_info.port = ntohs(sockaddr_client.sin_port);
		strcpy(aclient_info.addr,buffer);
		aclient_info.name[127] = '0';
		printf("name[127] has been set to 0, name: %s\n",aclient_info.name);
		printf("addr->%s:%u\n",aclient_info.addr,aclient_info.port);
		db_key.size = 128;
		db_key.data = aclient_info.name;

		db_data.size = sizeof(struct client_info);
		db_data.data = &aclient_info;
		ret_val = dbp->put(dbp,NULL,&db_key,&db_data,DB_NOOVERWRITE);
		db_print_err(ret_val,__LINE__);
		dbp->sync(dbp,0);
		
		ret_val = send(socket_client, "abcdefghijklmnopqrstuvwxyz",26,0);
		printf("send %d bytes\n",ret_val);
	}

	if(dbp != NULL){
		dbp->close(dbp,0);
	}
	close(socket_server);
	close(socket_client);

	return 0;
}

