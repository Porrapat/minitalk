all: client server

client:
	gcc client.c ft_utils.c ft_utils_2.c -o client
server:
	gcc server.c ft_utils.c ft_utils_2.c -o server

clean:

fclean: clean
	rm -rf client
	rm -rf server

