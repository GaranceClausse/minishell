/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:52:03 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/09 16:16:35 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(long nb, int add)
{
	long long	tmp;

	tmp = nb * 10 + add;
	return (((tmp - add) / 10) != nb);
}

static int	check_underflow(long nb, int add)
{
	long long	tmp;

	nb = -nb;
	tmp = nb * 10 - add;
	return ((tmp + add) / 10 != nb);
}

int	ft_atoi(const char *nptr)
{
	long		neg;
	long		nb;

	nb = 0;
	neg = 0;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg = 1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr) != 1)
	{
		if (!neg && check_overflow(nb, *nptr - '0'))
			return (-1);
		if (neg && check_underflow(nb, *nptr - '0'))
			return (0);
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	if (neg)
		nb = -nb;
	return ((int)nb);
}
