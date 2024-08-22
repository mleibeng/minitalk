/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:53:48 by mleibeng          #+#    #+#             */
/*   Updated: 2023/11/25 22:54:18 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	bin_to_char(int signum, char	*c)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c <<= 1 ;
}

void	sig_handler(int signum, siginfo_t	*info, void	*context)
{
	static int	pid;
	static int	i;
	static char	c;

	pid = info->si_pid;
	(void)context;
	bin_to_char(signum, &c);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;
	int					my_pid;

	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	my_pid = getpid();
	ft_printf("\033[0;35mSERVER PID: %d\033[31m\n", my_pid);
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
	while (1)
		pause();
	return (0);
}
