/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:52:03 by vkrajcov          #+#    #+#             */
/*   Updated: 2021/12/02 13:33:52 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

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
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg = 1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
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
