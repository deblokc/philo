/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:32:50 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/22 15:39:04 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_eat(pthread_mutex_t *forka, pthread_mutex_t *forkb, t_philo *philo)
{
	struct timeval	tmp;
	int				aislocked;
	int				bislocked;

	aislocked = 0;
	bislocked = 0;
	if (philo->info->alive && !aislocked++)
		pthread_mutex_lock(forka);
	if (philo->info->alive)
		print(" as taken a fork", philo->num, philo);
	while (philo->info->alive && !bislocked)
	{	
		if (philo->info->alive && !bislocked++)
			pthread_mutex_lock(forkb);
	}
	if (philo->info->alive)
		print(" as taken a fork", philo->num, philo);
	if (philo->info->alive)
		eating(philo, tmp);
	usleep(philo->info->time_to_eat * 1000);
	if (aislocked)
		pthread_mutex_unlock(forka);
	if (bislocked)
		pthread_mutex_unlock(forkb);
}

void	*thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->info->num_of_philo % 2 \
			&& philo->num == philo->info->num_of_philo - 2)
		usleep((philo->info->time_to_eat - 10) / 2 * 1000);
	if (!(philo->num % 2))
		usleep(philo->info->time_to_eat / 2 * 1000);
	while (philo->info->alive)
	{
		if (philo->info->num_of_philo == 1)
			return (usleep(philo->info->time_to_die * 1000), NULL);
		philo->as_eaten = 0;
		if (philo->num % 2 && philo->num != philo->info->num_of_philo \
				&& caneat(philo))
			try_eat(&philo->fork_r->mutex, &philo->fork_l->mutex, philo);
		else if (caneat(philo))
			try_eat(&philo->fork_l->mutex, &philo->fork_r->mutex, philo);
		if (caneat(philo) && philo->as_eaten)
			print(" is sleeping", philo->num, philo);
		if (caneat(philo) && philo->as_eaten)
			print(" is thinking", philo->num, philo);
		specialcase(philo);
	}
	return (NULL);
}

int	checkeat(t_info *info)
{
	t_philo	*current;

	current = info->first_philo;
	while (current != info->first_philo->prev)
	{
		if (current->count_eat != info->number_of_eat)
			return (0);
		current = current->next;
	}
	if (current->count_eat != info->number_of_eat)
		return (0);
	return (1);
}

void	reaper(t_info *info, struct timeval tmp, t_philo *current)
{
	while (info->alive)
	{
		gettimeofday(&tmp, NULL);
		if (getms(info, &tmp) - current->lastmeal > info->time_to_die)
		{
			info->alive = 0;
			usleep(1000);
			pthread_mutex_lock(&info->write);
			printf("%lu %d died\n", getms(info, &tmp), current->num);
			pthread_mutex_unlock(&info->write);
		}
		if (info->number_of_eat != -1 && checkeat(info))
		{
			info->alive = 0;
			break ;
		}
		current = current->next;
	}
}

void	start_philo(t_info *info)
{
	struct timeval	tmp;
	t_philo			*current;
	int				i;

	pthread_mutex_init(&info->write, NULL);
	info->alive = 1;
	gettimeofday(&info->timebegin, NULL);
	current = info->first_philo;
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_create(&info->thread[current->num - 1], NULL, thread, current);
		current = current->next;
		i++;
	}
	current = info->first_philo;
	reaper(info, tmp, current);
	while (current != info->first_philo->prev)
	{
		pthread_join(info->thread[current->num - 1], NULL);
		current = current->next;
	}
	pthread_join(info->thread[current->num - 1], NULL);
}
