.PHONY: all clean

all: client server db_print_client_list

client: socket_client.c
	gcc socket_client.c -o client

server: socket_server.c
	gcc socket_server.c -o server -ldb

#db_print_client_list.c
db_print_client_list: db_print_client_list.c
	gcc db_print_client_list.c -ldb -o db_print_client_list
clean:
	rm client server dd_print_client_list

