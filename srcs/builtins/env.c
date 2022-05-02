/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:07:30 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/02 15:49:53 by gclausse         ###   ########.fr       */
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
		if (ft_strchr(env_var->list[i], '='))
		{
			ft_printf("%s\n", env_var->list[i]);
			
		}
		i++;
	}
	return (0);
}
