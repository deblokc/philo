/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:12:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/22 15:38:47 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				num;
	struct s_philo	*philo_r;
	struct s_philo	*philo_l;
}			t_fork;

typedef struct s_philo
{
	_Atomic int				as_eaten;
	_Atomic int				count_eat;
	struct s_info			*info;
	int						num;
	t_fork					*fork_r;
	t_fork					*fork_l;
	struct s_philo			*next;
	struct s_philo			*prev;
	_Atomic unsigned long	lastmeal;
}			t_philo;

typedef struct s_info
{
	pthread_mutex_t		write;
	_Atomic int			alive;
	struct timeval		timebegin;
	int					num_of_philo;
	unsigned long		time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_eat;
	t_philo				*first_philo;
	pthread_t			*thread;
}		t_info;

typedef struct s_data
{
	t_info	*info;
	t_info	*philo;
}				t_data;
void			eating(t_philo *philo, struct timeval tmp);
int				caneat(t_philo *philo);
t_philo			*new_philo(int i);
t_fork			*new_fork(int i);
void			init_next(t_philo **current, t_info *info, int i);
unsigned long	getms(t_info *info, struct timeval *tmp);
long long		ft_atoi(char *str);
int				ft_isdigit(int c);
void			start_philo(t_info *info);
void			print(char *str, int num, t_philo *philo);
void			specialcase(t_philo *philo);
#endif
