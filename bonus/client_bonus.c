/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:53:51 by mleibeng          #+#    #+#             */
/*   Updated: 2023/11/25 23:09:38 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static volatile sig_atomic_t	g_receive_stop;

void	error_check(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
	{
		ft_printf("Wrong amount of arguments!");
		exit(EXIT_FAILURE);
	}
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			ft_printf("Wrong Server PID!");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return ;
}

void	sig_handler(int signum, siginfo_t	*info, void	*context)
{
	static int	i;

	(void)context;
	(void)info;
	g_receive_stop = 1;
	if (signum == SIGUSR2)
	{
		i++;
		usleep(10);
	}
	else if (signum == SIGUSR1)
	{
		ft_printf("\033[0;35mbytes received: %d\033[0m\n", (i / 8));
		i = 0;
	}
	return ;
}

int	char_to_bin(char c, int pid)
{
	int	iterate;
	int	index;

	index = 7;
	while (index >= 0)
	{
		iterate = 0;
		if ((c >> index) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_receive_stop)
		{
			if (iterate == 80)
			{
				ft_printf("\033[31mNo response\033[0m\n");
				exit(EXIT_SUCCESS);
			}
			iterate++;
			usleep(100);
		}
		g_receive_stop = 0;
		index--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					i;
	pid_t				server_pid;

	sa.sa_sigaction = &sig_handler;
	error_check(argc, argv);
	i = 0;
	server_pid = ft_atoi(argv[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Error in sigaction Signal SIGURS1");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error in sigaction Signal SIGURS2");
		exit(EXIT_FAILURE);
	}
	while (argv[2][i])
		char_to_bin(argv[2][i++], server_pid);
	char_to_bin('\n', server_pid);
	char_to_bin('\0', server_pid);
	return (0);
}
