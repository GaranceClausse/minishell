/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:07:30 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/29 15:29:09 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_env(char **args, t_var_list *env_var)
{
	int	i;
	char *var_value;

	i = 0;
	if (*args)
	{
		write (2, "env: too many arguments\n", 25);
		return (1);
	}
	while (env_var->list[i])
	{
		var_value = extract_var_value(env_var->list[i]);
		if (var_value[0] != '\'')
		{
			write (1, env_var->list[i], ft_strlen(env_var->list[i]));
			write (1, "\n", 1);
			free(var_value);
		}
		i++;
	}
	return (0);
}
