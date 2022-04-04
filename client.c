/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetchda <ppetchda@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                              +#+#+#+#+#+     +#+           */
/*   Created: 2022/03/31 20:13:59 by ppetchda          #+#    #+#             */
/*   Updated: 2022/03/31 20:18:35 by ppetchda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static int server_pid = 0;
static char *current_str;

static void	kill_with_check(int pid, int sig)
{
	int	ret;

	ret = 0;
	usleep(1000);
	if (pid == -1 || pid == 0)
	{
		ft_putendl_fd("Not Support Process ID 0 or -1.", 1);
		exit(0);
	}
	ret = kill(pid, sig);
	if (ret == -1)
	{
		ft_putendl_fd("Invalid Process ID.", 1);
		exit(0);
	}
}

static void	client_action(int sig, siginfo_t *info, void *context)
{
	static int	shifted_bit = 1;
	static int	shifted_byte = 0;
	char	c;

	c = *(current_str + shifted_byte);
	// write(1, &c, 1);

	

	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (shifted_bit >= 8)
		{
			shifted_bit = 0;
			shifted_byte++;
			ft_putstr_fd("x", 1);
			if (*(current_str + shifted_byte) == '\0')
			{
				ft_putstr_fd("Send Complete! Byte sent : ", 1);
				ft_putnbr_fd(shifted_byte, 1);
				ft_putstr_fd("\n", 1);
				ft_putstr_fd("z", 1);
				kill_with_check(server_pid, SIGUSR1);
				exit(0);
			}
		}
		if ((c << shifted_bit++) & 0x80)
		{
			write(1, &"1", 1);
			kill(server_pid, SIGUSR1);
		}
		else
		{
			write(1, &"0", 1);
			kill(server_pid, SIGUSR2);
		}
	}
	
}



static void	first_kill(char *str)
{
	char	c;

	c = *str;
	if (c & 0x80)
	{
		write(1, &"1", 1);
		kill_with_check(server_pid, SIGUSR1);
	}
	else
	{
		write(1, &"0", 1);
		kill_with_check(server_pid, SIGUSR2);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;

	ft_memset(&s_sigaction, 0, sizeof(s_sigaction));
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putendl_fd("Using with:", 1);
		ft_putendl_fd("./client <process_id> <message>", 1);
		return (1);
	}
	s_sigaction.sa_sigaction = client_action;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	server_pid = ft_atoi(argv[1]);
	current_str = argv[2];
	first_kill(current_str);
	while (1)
		pause();
	return (0);
}

