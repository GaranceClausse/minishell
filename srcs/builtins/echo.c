/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:54:51 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/11 20:59:12 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	is_only_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(char **args)
{
	int	new_line;

	new_line = 1;
	while (*args && *args[0] == '-')
	{
		if (ft_strlen(*args) > 1 && is_only_n(*args + 1))
			new_line = 0;
		else
			break ;
		args++;
	}
	if (*args)
	{
		ft_putstr_fd(*args, 1);
		args++;
	}
	while (*args)
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(*args, 1);
		args++;
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}
