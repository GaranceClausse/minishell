/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:22:10 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/11 14:37:06 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

static void	check_arg(t_combo *combo, char **args)
{
	int	i;

	i = 0;
	while (args[0][i])
	{
		if (ft_isdigit(args[0][i]) == 1 && ft_isspace(args[0][i]) != 1)
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			free_before_exit(combo, args - 1);
			exit(2);
		}
		i++;
	}
}

void	exit_builtin(t_combo *combo, char **args, int is_in_pipe)
{
	int	ret;

	if (!is_in_pipe)
		ft_putstr_fd("exit\n", 2);
	if (!args[0])
	{
		free_before_exit(combo, args - 1);
		exit(g_last_return);
	}	
	check_arg(combo, args);
	ret = ft_atoi(args[0]);
	free_before_exit(combo, args - 1);
	if (ret >= 0 && ret <= 255)
		exit(ret);
	exit(129);
}
