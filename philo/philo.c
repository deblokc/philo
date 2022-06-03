/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:07:56 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/11 12:46:44 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_info *info)
{
	int		i;
	t_philo	*current;

	i = 1;
	while (i <= info->num_of_philo)
	{
		if (!info->first_philo)
		{
			info->first_philo = new_philo(i);
			current = info->first_philo;
			current->info = info;
			current->fork_r = new_fork(i);
			current->fork_r->philo_l = current;
		}
		else
			init_next(&current, info, i);
		i++;
	}
	current->next = info->first_philo;
	info->first_philo->prev = current;
	info->first_philo->fork_l = current->fork_r;
	current->fork_r->philo_r = info->first_philo;
}

int	checkarg(char **av, int num)
{
	int	i;
	int	j;

	i = 1;
	while (i <= num)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	freeinfo(t_info *info)
{
	t_philo	*current;
	t_philo	*last;
	t_philo	*tmp;

	last = info->first_philo->prev;
	current = info->first_philo;
	while (current != last)
	{
		pthread_mutex_destroy(&current->fork_r->mutex);
		free(current->fork_r);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	free(info->thread);
	free(current->fork_r);
	free(current);
}

int	main(int ac, char **av)
{
	t_info	info;

	if ((ac == 5 && checkarg(av, 4)) || (ac == 6 && checkarg(av, 5)))
	{
		info.num_of_philo = ft_atoi(av[1]);
		info.time_to_die = ft_atoi(av[2]);
		info.time_to_eat = ft_atoi(av[3]);
		info.time_to_sleep = ft_atoi(av[4]);
		info.number_of_eat = -1;
		if (ac == 6)
			info.number_of_eat = ft_atoi(av[5]);
		info.first_philo = NULL;
		info.thread = (pthread_t *)malloc(sizeof(pthread_t) \
				* info.num_of_philo);
		init_philo(&info);
		start_philo(&info);
		freeinfo(&info);
	}
	return (0);
}
