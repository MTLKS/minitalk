/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:47:06 by maliew            #+#    #+#             */
/*   Updated: 2022/07/29 02:04:38 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	sig_action(int signum, siginfo_t *info, void *context)
{
	static pid_t	c_pid = 0;
	static int		bit_count = 0;
	static char		c = 0;

	(void)(context);
	if (c_pid != info->si_pid)
		c_pid = info->si_pid;
	else
	{
		c |= (signum == SIGUSR2);
		if (++bit_count == 8)
		{
			bit_count = 0;
			if (!c)
			{
				kill(c_pid, SIGUSR2);
				return ;
			}
			ft_putchar_fd(c, 1);
			c = 0;
		}
		else
			c <<= 1;
	}
	kill(c_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sa.sa_sigaction = sig_action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
