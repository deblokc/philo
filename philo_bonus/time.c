/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:42:00 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/21 19:23:14 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	getms(t_info *info, struct timeval *new)
{
	return (((new->tv_sec - info->timebegin.tv_sec) * 1000) + \
			((new->tv_usec - info->timebegin.tv_usec)) / 1000);
}

int	caneat(t_philo *philo)
{
	if (philo->info->alive->__align)
		return (1);
	return (0);
}

int	seminfo(t_info *info)
{
	info->helper = (pthread_t *)malloc(sizeof(pthread_t) * info->num_of_philo);
	if (!info->helper)
		return (1);
	init_philo(info);
	philo_launch(info);
	freeinfo(info);
	sem_close(info->fork);
	sem_close(info->alive);
	sem_close(info->print);
	sem_close(info->alleat);
	sem_unlink("alleat");
	sem_unlink("alive");
	sem_unlink("print");
	sem_unlink("sem");
	return (0);
}

void	philo_launch2(t_info *info)
{
	t_philo	*current;
	int		i;

	current = info->first_philo;
	i = 0;
	while (i < info->num_of_philo)
	{
		if (!(current->num % 2))
		{
			current->pid = fork();
			if (current->pid == 0)
				philo(info, current->num);
		}
		current = current->next;
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	philo_launch(t_info *info)
{
	t_philo	*current;
	int		i;

	i = 0;
	gettimeofday(&info->timebegin, NULL);
	current = info->first_philo;
	while (i < info->num_of_philo)
	{
		if (current->num % 2)
		{
			current->pid = fork();
			if (current->pid == 0)
				philo(info, current->num);
		}
		current = current->next;
		i++;
	}
	usleep((info->time_to_eat / 2) * 1000);
	philo_launch2(info);
}
