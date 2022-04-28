/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:07:30 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/28 16:25:41 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_env(char **args, t_var_list *env_var)
{
	int	i;

	i = 0;
	if (*args)
	{
		write (2, "env: too many arguments\n", 25);
		return (1);
	}
	while (env_var->list[i])
	{
		write (1, env_var->list[i], ft_strlen(env_var->list[i]));
		write (1, "\n", 1);
		i++;
	}
	return (0);
}
