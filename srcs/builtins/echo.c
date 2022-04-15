/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:54:51 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/15 15:09:39 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	echo(char **args)
{
	int	new_line;
	int	i;

	new_line = 1;
	if (args)
	{
		i = 0;
		if (args[0] && !ft_strcmp(args[0], "-n"))
		{
			new_line = 0;
			i = 1;
		}
		if (args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			i++;
		}
		while (args[i])
		{
			write(1, " ", 1);
			write(1, args[i], ft_strlen(args[i]));
			i++;
		}
	}
	if (new_line)
		write(1, "\n", 1);
}