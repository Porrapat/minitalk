# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppetchda <ppetchda@student.42bangkok.com>  +#+  +:+       +#+         #
#                                               +#+#+#+#+#+     +#+            #
#    Created: 2022/03/31 20:13:59 by ppetchda          #+#    #+#              #
#    Updated: 2022/03/31 20:18:35 by ppetchda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

$(NAME): all

all: client server

client:
	gcc -Wall -Wextra -Werror client.c ft_utils.c ft_utils_2.c -o client
server:
	gcc -Wall -Wextra -Werror server.c ft_utils.c ft_utils_2.c -o server

clean:

fclean: clean
	rm -rf client
	rm -rf server

bonus: re all

re: fclean all

norminette:
	norminette server.c
	norminette client.c
	norminette ft_utils.c
	norminette ft_utils_2.c
	norminette minitalk.h