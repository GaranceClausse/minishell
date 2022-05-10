/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:22:10 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/10 17:02:27 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

void	exit_builtin(t_combo *combo, char **args, int is_in_pipe)
{
	int	i;
	int	ret;

	i = 0;
	if (!is_in_pipe)
		write(2, "exit\n", 6);
	if (!args[0])
	{
		free_before_exit(combo, args - 1);
		exit(g_last_return);
	}	
	while (args[0][i])
	{
		if (ft_isdigit(args[0][i]) == 1 && ft_isspace(args[0][i]) != 1)
		{
			write (2, "exit: numeric argument required\n", 32);
			free_before_exit(combo, args - 1);
			exit(2);
		}
		i++;
	}
	ret = ft_atoi(args[0]);
	free_before_exit(combo, args - 1);
	if (ret >= 0 && ret <= 255)
		exit(ret);
	exit(129);
}
