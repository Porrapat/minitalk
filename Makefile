all: client server

client:
	gcc -g client.c ft_utils.c ft_utils_2.c -o client
server:
	gcc -g server.c ft_utils.c ft_utils_2.c -o server

clean:

fclean: clean
	rm -rf client
	rm -rf server

re: fclean all

norminette:
	norminette server.c
	norminette client.c
	norminette ft_utils.c
	norminette ft_utils_2.c
	norminette minitalk.h