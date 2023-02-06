/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:24:17 by asaber            #+#    #+#             */
/*   Updated: 2023/02/06 13:56:17 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	exponin(int i, int n)
{
	int	x;

	x = i;
	if (n == 0)
		return (1);
	while (n-- > 1)
		i *= x;
	return (i);
}

void	ft_putnbr(int nb)
{
	long	b;
	char	c;

	b = nb;
	if (b < 0)
	{
		write(1, "-", 1);
		b = -b;
	}
	if (b >= 10)
	{
		ft_putnbr(b / 10);
		c = b % 10 + 48;
		write(1, &c, 1);
	}
	if (b < 10)
	{
		c = b % 10 + 48;
		write(1, &c, 1);
	}
}

void	sig_handler(int a, siginfo_t *infos, void *old_action)
{
	static int				i;
	static int				var;
	static char				str_bin;
	static pid_t			pid_client;

	(void) *old_action;
	if (pid_client != infos->si_pid)
	{
		pid_client = infos->si_pid;
		i = 0;
		var = 0;
	}
	if (a == SIGUSR2)
		var += exponin(2, i);
	i++;
	if (i == 8)
	{
		str_bin = var;
		write(1, &str_bin, 1);
		i = 0;
		var = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
}
