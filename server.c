/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetchda <ppetchda@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                              +#+#+#+#+#+     +#+           */
/*   Created: 2022/03/31 20:13:59 by ppetchda          #+#    #+#             */
/*   Updated: 2022/03/31 20:18:35 by ppetchda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <limits.h>
#include <stdio.h>
char *chartobin ( unsigned char c )
{
    static char bin[CHAR_BIT + 1] = {0};
    int i;
    for( i = CHAR_BIT - 1; i >= 0; i-- )
    {
        bin[i] = (c % 2) + '0';
        c /= 2;
    }
   	return bin;
}

// void test_print_binary(void) {
// 	char a = 42;
// 	int i;
// 	for (i = 0; i < 8; i++) {
// 	//	ft_putnbr_fd(((a << i) & 0x80), 1);
// 	//	ft_putstr_fd("x", 1);
// 		ft_putnbr_fd(!!((a << i) & 0x80), 1);
// 	}
// 	ft_putstr_fd("\n", 1);
// }

static void	server_action(int sig, siginfo_t *info, void *context)
{
	// kill -s 10 <pid>
	// kill -s 12 <pid>
	printf("Bin 42 is %s\n", chartobin(42));
	ft_putstr_fd("Hey Recieved : \n", 1);
}

int	main(void)
{
	int					pid;
	struct sigaction	s_sigaction;

	// test_print_binary();

	ft_memset(&s_sigaction, 0, sizeof(s_sigaction));
	pid = getpid();
	ft_putstr_fd("Server, PID is : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	s_sigaction.sa_sigaction = server_action;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);

	while (1)
		pause();
	return (0);
}
