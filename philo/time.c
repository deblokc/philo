/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:42:00 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/10 12:47:37 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	getms(t_info *info, struct timeval *new)
{
	return (((new->tv_sec - info->timebegin.tv_sec) * 1000) + \
			((new->tv_usec - info->timebegin.tv_usec)) / 1000);
}
