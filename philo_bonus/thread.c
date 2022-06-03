/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:27:12 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/22 16:34:08 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*helper(void *arg)
{
	t_philo			*philo;
	struct timeval	tmp;

	philo = (t_philo *)arg;
	while (philo->info->alive->__align && \
			philo->info->alleat->__align != philo->info->num_of_philo)
	{
		sem_wait(philo->eat);
		gettimeofday(&tmp, NULL);
		if (getms(philo->info, &tmp) - philo->last_eat \
				> philo->info->time_to_die && philo->info->alive->__align == 1)
		{
			sem_wait(philo->info->print);
			if (philo->info->alive->__align == 1)
			{
				sem_wait(philo->info->alive);
				printf("%ld %d died\n", getms(philo->info, &tmp), \
						philo->num);
			}
			sem_post(philo->info->print);
		}
		sem_post(philo->eat);
		usleep(1000);
	}
	return (NULL);
}
