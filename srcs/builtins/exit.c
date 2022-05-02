/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:22:10 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/02 16:16:01 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exit_builtin(char **args)
{
	int	i;

	i = 0;
	if (*args)
	{
		write(2, "exit\n", 6);
		while (args[0][i])
		{
			if (ft_isdigit(args[0][i]) == 0)
			{
				write (2, "exit: numeric argument required\n", 32);
				exit(2);
			}
			i++;
		}
		if (ft_atoi(args[0]) >= 0 && ft_atoi(args[0]) <= 255)
			exit(ft_atoi(args[0]));
		else
			exit(129);
	}
}
