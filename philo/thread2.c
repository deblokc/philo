/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:43:06 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/22 15:38:31 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, struct timeval tmp)
{
	gettimeofday(&tmp, NULL);
	philo->lastmeal = getms(philo->info, &tmp);
	print(" is eating", philo->num, philo);
	philo->count_eat++;
	philo->as_eaten = 1;
}

void	specialcase(t_philo *philo)
{
	usleep(1000);
	if (philo->info->time_to_sleep < philo->info->time_to_eat)
		usleep((philo->info->time_to_eat - philo->info->time_to_sleep) * 1000);
	if (philo->info->num_of_philo % 2 \
			&& philo->num == philo->info->num_of_philo)
		usleep(philo->info->time_to_eat / 2 * 1000);
}

int	caneat(t_philo *philo)
{
	if (philo->info->alive \
				&& philo->count_eat != philo->info->number_of_eat)
		return (1);
	return (0);
}
