/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:22:14 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/22 16:39:17 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_eat(t_philo *philo)
{
	struct timeval	tmp;

	if (philo->info->alive->__align)
	{
		sem_wait(philo->info->fork);
		sem_wait(philo->eat);
		if (philo->info->alive->__align)
			print(" as taken a fork", philo->num, philo);
		sem_wait(philo->info->fork);
		if (philo->info->alive->__align)
			print(" as taken a fork", philo->num, philo);
		gettimeofday(&tmp, NULL);
		philo->last_eat = getms(philo->info, &tmp);
		if (philo->info->alive->__align)
		{
			print(" is eating", philo->num, philo);
			philo->count_eat++;
		}
		sem_post(philo->eat);
		usleep(philo->info->time_to_eat * 1000);
	}
	sem_post(philo->info->fork);
	sem_post(philo->info->fork);
}

void	freephilo(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*last;

	pthread_join(philo->info->helper[philo->num - 1], NULL);
	sem_close(philo->eat);
	sem_close(philo->info->alleat);
	sem_close(philo->info->alive);
	sem_close(philo->info->print);
	sem_close(philo->info->fork);
	free(philo->info->helper);
	free(philo->eat_str);
	last = philo->prev;
	while (philo != last)
	{
		tmp = philo;
		philo = philo->next;
		free(tmp);
	}
	free(philo);
}

void	routine(t_philo *philo)
{
	while (philo->info->alive->__align && (long)philo->info->alleat->__align \
			< (long)philo->info->num_of_philo)
	{
		if (caneat(philo))
			try_eat(philo);
		if (caneat(philo))
			print(" is sleeping", philo->num, philo);
		if (caneat(philo))
			usleep(philo->info->time_to_sleep * 1000);
		if (caneat(philo))
			print(" is thinking", philo->num, philo);
		if (philo->count_eat == philo->info->number_of_eat)
			sem_post(philo->info->alleat);
		if (philo->info->num_of_philo % 2 \
				&& philo->num == philo->info->num_of_philo)
			usleep((philo->info->time_to_eat / 2) * 1000);
	}
}

void	philo(t_info *info, int num)
{
	t_philo	*philo;

	philo = info->first_philo;
	while (philo->num != num)
		philo = philo->next;
	philo->eat_str = ft_itoa(philo->num);
	sem_unlink(philo->eat_str);
	philo->eat = sem_open(philo->eat_str, O_CREAT, 777, 1);
	pthread_create(&info->helper[philo->num - 1], NULL, helper, philo);
	if (philo->info->num_of_philo != 1)
		routine(philo);
	else
		usleep(philo->info->time_to_die * 1000);
	freephilo(philo);
	exit(0);
}
