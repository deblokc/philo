/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:13:57 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/21 19:24:00 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	sem_t			*eat;
	char			*eat_str;
	struct s_info	*info;
	struct s_philo	*next;
	struct s_philo	*prev;
	unsigned long	last_eat;
	int				num;
	pid_t			pid;
	int				count_eat;
}	t_philo;

typedef struct s_info
{
	pthread_t		*helper;
	sem_t			*alleat;
	pthread_t		reaper;
	sem_t			*print;
	sem_t			*fork;
	struct timeval	timebegin;
	sem_t			*alive;
	t_philo			*first_philo;
	int				num_of_philo;
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
}					t_info;

void			*helper(void *arg);
int				caneat(t_philo *philo);
void			init_philo(t_info *info);
void			freeinfo(t_info *info);
int				seminfo(t_info *info);
int				ft_isdigit(int c);
long long		ft_atoi(const char *str);
void			philo_launch(t_info *info);
void			print(char *str, int i, t_philo *philo);
unsigned long	getms(t_info *info, struct timeval *time);
char			*ft_itoa(int n);
void			philo(t_info *info, int num);
#endif
