all: client server

client:
	gcc client.c -o client
server:
	gcc server.c -o server

clean:

fclean: clean
	rm -rf client
	rm -rf server

