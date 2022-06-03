/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:10:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/02/28 15:23:16 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoi(const char *nptr)
{
	int			i;
	int			neg;
	long long	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while (nptr[i] == '\f' || nptr[i] == '\t' || nptr[i] == '\v'
		|| nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] && nptr[i] == '-')
	{
		neg *= -1;
		i++;
	}
	else if (nptr[i] && nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((nbr * -1) < -2147483648)
			return (nbr);
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (neg * nbr);
}
