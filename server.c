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
#include <stdio.h>
#include <limits.h>

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

// static void	server_action(int sig, siginfo_t *info, void *context)
// {
// 	static int				i = 7;
// 	static unsigned char	c = 0;

// 	// '0' is 00110000
// 	(void)context;

// 	ft_putstr_fd("i is ", 1);
// 	ft_putnbr_fd(i, 1);
// 	ft_putstr_fd("\n", 1);
// 	if (i <= -1)
// 	{
		
// 		write(1, &c, 1);
// 		i = 7;
// 		c = 0;
// 		kill(info->si_pid, SIGUSR2);
// 	}
// 	else
// 	{
// 		if (sig == SIGUSR1)
// 			c |= (1 << i--);
// 		else
// 			c |= (0 << i--);
// 		kill(info->si_pid, SIGUSR1);
// 	}
// }

void	server_action(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int	i = -1;

	(void)context;
	if (i < 0)
		i = 7;
	if (sig == SIGUSR1)
		c |= 1 << i;
	else if (sig == SIGUSR2)
		c &= ~(1 << i);
	if (!i && c)
		ft_putchar_fd(c, 1);
	else if (!i && !c)
		kill(info->si_pid, SIGUSR2);
	i--;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	s_sigaction;

	ft_memset(&s_sigaction, 0, sizeof(s_sigaction));
	pid = getpid();
	ft_putstr_fd("Server, PID is : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	s_sigaction.sa_sigaction = server_action;
	s_sigaction.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
