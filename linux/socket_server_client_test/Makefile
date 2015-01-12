.PHONY: all clean

all: client server

client: socket_client.c
	gcc socket_client.c -o client

server: socket_server.c
	gcc socket_server.c -o server

clean:
	rm client server

