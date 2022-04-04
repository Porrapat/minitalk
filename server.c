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

static void	server_action(int sig, siginfo_t *info, void *context)
{
	static int				i = 7;
	static unsigned char	c = 0;

	(void)context;
	if (sig == SIGUSR1)
	{
		c |= (1 << i--);
		kill(info->si_pid, SIGUSR1);
	}
	else if (sig == SIGUSR2)
	{
		c |= (0 << i--);
		kill(info->si_pid, SIGUSR1);
	}
	if (i == -1)
	{
		ft_putchar_fd(c, 1);
		kill(info->si_pid, SIGUSR2);
		i = 7;
		c = 0;
	}
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
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
