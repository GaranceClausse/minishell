/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_what_kind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:15:39 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/08 21:41:15 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (0);
	else
		return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else
		return (1);
}

int	ft_isunderscore(int c)
{
	if (c == '_')
		return (0);
	else
		return (1);
}

int	is_valid_identifier(char *str, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if ((ft_isalnum(arg[i]) && ft_isdigit(arg[i])
				&& ft_isunderscore(arg[i])) || ft_isdigit(arg[0]) == 0)
		{
			printf("%s: '%s' : not a valid identifier\n", str, arg);
			return (1);
		}
		i++;
	}
	return (0);
}
