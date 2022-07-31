/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:09:57 by maliew            #+#    #+#             */
/*   Updated: 2022/07/30 22:19:20 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*g_msg;

static void	mt_exit(char *str)
{
	ft_printf(str);
	if (g_msg)
		free(g_msg);
	exit(0);
}

static void	sig_action(int signum, siginfo_t *info, void *context)
{
	static int		byte_count = 0;
	static int		bit_count = 8;
	static pid_t	server_pid;
	char			c;

	(void)(context);
	if (info->si_pid != 0)
		server_pid = info->si_pid;
	if (signum == SIGUSR2)
		mt_exit("Message sent successfully.\n");
	else
	{
		if (--bit_count < 0)
		{
			bit_count = 7;
			byte_count++;
		}
		c = g_msg[byte_count];
		if (c && ((c >> bit_count) & 1))
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
		mt_exit("Wrong number of arguments.\n");
	sa.sa_sigaction = sig_action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	g_msg = ft_strdup(argv[2]);
	if (kill(ft_atoi(argv[1]), SIGUSR1) == -1)
		mt_exit("Connection error.\n");
	while (1)
		pause();
}
