/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:43:56 by asaber            #+#    #+#             */
/*   Updated: 2023/02/06 13:56:26 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_isdigit(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] >= '0' && c[i] <= '9')
			i++;
		else
		{
			write(1, "pid is not correct\n", 19);
			return (0);
		}
	}
	return (1);
}

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
}

int	main(int argc, char **argv)
{
	int	send_pid;

	if (argc == 3 && ft_isdigit(argv[1]))
	{
		send_pid = ft_atoi(argv[1]);
		if (!send_pid)
		{
			write(1, "pid is not correct\n", 19);
			return (0);
		}
		sig_send(send_pid, argv[2]);
	}
	return (0);
}
