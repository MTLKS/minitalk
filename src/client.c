/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:09:57 by maliew            #+#    #+#             */
/*   Updated: 2022/07/29 02:10:37 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*g_msg;

static void	sig_action(int signum, siginfo_t *info, void *context)
{
	static int	byte_count = 0;
	static int	bit_count = 8;
	static char	c = 0;

	(void)(context);
	if (signum == SIGUSR2)
	{
		ft_printf("Message sent successfully\n");
		free(g_msg);
		exit(0);
	}
	else
	{
		if (--bit_count < 0)
		{
			bit_count = 7;
			byte_count++;
		}
		c = g_msg[byte_count];
		if (c && ((c >> bit_count) & 1))
			kill(info->si_pid, SIGUSR2);
		else
			kill(info->si_pid, SIGUSR1);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	if (argc != 3)
		return (0);
	sa.sa_sigaction = sig_action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = ft_atoi(argv[1]);
	g_msg = ft_strdup(argv[2]);
	if (kill(pid, SIGUSR1) != -1)
	{
		while (1)
			pause();
	}
	ft_printf("Connection error.\n");
	free(g_msg);
	return (0);
}
