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

static void	server_action(int sig, siginfo_t *info, void *context)
{
	// kill -s 10 <pid>
	// kill -s 12 <pid>

	static int				i = 7;
	static unsigned char	c = 0;

	// printf("Bin 42 is %s\n", chartobin(42));
	// ft_putstr_fd("Hey Recieved From : ", 1);
	// ft_putnbr_fd(info->si_pid, 1);
	// ft_putstr_fd("\n", 1);
	if (sig == SIGUSR1)
	{
		// ft_putstr_fd("SIGUSR2\n", 1);
		c |= (1 << i--);
	}
	else if (sig == SIGUSR2)
	{
		c |= (0 << i--);
		// ft_putstr_fd("SIGUSR1\n", 1);
	}
	printf("Bin 42 is %s\n", chartobin(c));
	if (i == -1)
	{
		printf("Char is %c\n", c);
		i = 7;
		c = 0;
	}
	// if(sig = SI)
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
