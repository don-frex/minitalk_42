/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:17:08 by asaber            #+#    #+#             */
/*   Updated: 2023/02/06 13:56:33 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *c)
{
	int	i;
	int	sign;
	int	res;

	sign = 1;
	i = 0;
	res = 0;
	while (c[i] == 32 || (c[i] >= 9 && c[i] <= 13))
		i++;
	if (c[i] == '-' || c[i] == '+')
	{
		if (c[i] == '-')
			sign *= -1;
		i++;
	}
	while (c[i] >= '0' && c[i] <= '9')
	{
		res *= 10;
		res += c[i] - 48;
		i++;
	}
	return (res * sign);
}

void	kill_end(int t_getpid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(t_getpid, SIGUSR1);
		usleep(150);
		i++;
	}
}

void	sig_send(int t_getpid, char *a)
{
	int	i;
	int	j;

	j = 0;
	while (a[j])
	{
		i = 0;
		while (i < 8)
		{
			if (a[j] & 1)
				kill(t_getpid, SIGUSR2);
			else
				kill(t_getpid, SIGUSR1);
			a[j] = a[j] >> 1;
			usleep(150);
			i++;
		}
		j++;
	}
	kill_end(t_getpid);
}

void	si_done(int a)
{
	if (a == 30)
	{
		write(1, "sent", 4);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa_client;
	int					send_pid;

	if (argc == 3)
	{
		sa_client.sa_handler = si_done;
		sa_client.sa_flags = 0;
		sigaction(SIGUSR1, &sa_client, 0);
		send_pid = ft_atoi(argv[1]);
		sig_send(send_pid, argv[2]);
		while (1)
			pause();
	}
	return (0);
}
