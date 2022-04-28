/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:54:51 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/28 11:32:12 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	echo(char **args)
{
	int	new_line;

	new_line = 1;
	while (*args && !ft_strcmp(*args, "-n"))
	{
		new_line = 0;
		args++;
	}
	if (*args)
	{
		if (write(1, *args, ft_strlen(*args)) == -1)
			return (1);
		args++;
	}
	while (*args)
	{
		if (write(1, " ", 1) == -1 || write(1, *args, ft_strlen(*args)) == -1)
			return (1);
		args++;
	}
	if (new_line)
		if (write(1, "\n", 1))
			return (1);
	return (0);
}
