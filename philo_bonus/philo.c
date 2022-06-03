/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:35:30 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/18 14:23:11 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo	*new_philo(int i)
{
	t_philo	*tmp;

	tmp = (t_philo *)malloc(sizeof(t_philo));
	tmp->num = i;
	tmp->count_eat = 0;
	tmp->last_eat = 0;
	return (tmp);
}

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
		}
		else
		{
			current->next = new_philo(i);
			current->next->prev = current;
			current = current->next;
			current->info = info;
		}
		i++;
	}
	current->next = info->first_philo;
	info->first_philo->prev = current;
}

void	freeinfo(t_info *info)
{
	t_philo	*current;
	t_philo	*tmp;
	t_philo	*last;

	last = info->first_philo->prev;
	current = info->first_philo;
	while (current != last)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	free(current);
	free(info->helper);
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
		sem_unlink("sem");
		sem_unlink("print");
		sem_unlink("alive");
		sem_unlink("alleat");
		info.alleat = sem_open("alleat", O_CREAT, 777, 0);
		info.alive = sem_open("alive", O_CREAT, 777, 1);
		info.print = sem_open("print", O_CREAT, 777, 1);
		info.fork = sem_open("sem", O_CREAT, 777, info.num_of_philo);
		seminfo(&info);
	}
}
