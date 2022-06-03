/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:35:41 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/21 17:32:51 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_size(unsigned long nb)
{
	unsigned int	size;

	size = 0;
	while (nb > 9)
	{
		nb /= 10;
		size++;
	}
	return (++size);
}

static long	power(int n, int power)
{
	long	rep;

	rep = 1;
	while (power-- > 0)
		rep *= n;
	return (rep);
}

void	ft_putnbr(unsigned long nb)
{
	int				pow;
	char			c;

	pow = ft_size(nb);
	while (pow-- > 0)
	{	
		c = ((nb / power(10, pow)) + '0');
		write(1, &c, 1);
		nb = (nb % power(10, pow));
	}
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	print(char *str, int num, t_philo *philo)
{
	struct timeval	tmp;

	pthread_mutex_lock(&philo->info->write);
	gettimeofday(&tmp, NULL);
	ft_putnbr(getms(philo->info, &tmp));
	write(1, " ", 1);
	ft_putnbr((unsigned long)num);
	ft_putstr(str);
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->info->write);
	if (str[4] == 's')
		usleep(philo->info->time_to_sleep * 1000);
}
