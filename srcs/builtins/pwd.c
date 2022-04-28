/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:08:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/28 12:14:13 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(char **args, t_env *env)
{
	int		i;
	char	*cur_dir;

	if (*args)
	{
		write (1, "pwd: too many arguments\n", 25);
		return (1);
	}
	i = search_in_env(&env->env_var, "PWD", 3);
	if (i == -1)
	{
		write(1, "PWD not found\n", 15);
		return (1);
	}
	cur_dir = extract_var_value(env->env_var.list[i]);
	if (!cur_dir)
		return (1);
	write (1, cur_dir, ft_strlen(cur_dir));
	write(1, "\n", 2);
	free(cur_dir);
	return (0);
}
