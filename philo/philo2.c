/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:07:08 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/11 12:53:36 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(int i)
{
	t_philo	*tmp;

	tmp = (t_philo *)malloc(sizeof(t_philo));
	tmp->num = i;
	tmp->lastmeal = 0;
	tmp->count_eat = 0;
	return (tmp);
}

t_fork	*new_fork(int i)
{
	t_fork	*tmp;

	tmp = (t_fork *)malloc(sizeof(t_fork));
	tmp->num = i;
	pthread_mutex_init(&tmp->mutex, NULL);
	return (tmp);
}

void	init_next(t_philo **current, t_info *info, int i)
{
	(*current)->next = new_philo(i);
	(*current)->next->prev = (*current);
	(*current)->fork_r->philo_r = (*current)->next;
	(*current)->next->fork_l = (*current)->fork_r;
	(*current) = (*current)->next;
	(*current)->info = info;
	(*current)->fork_r = new_fork(i);
	(*current)->fork_r->philo_l = (*current);
}
