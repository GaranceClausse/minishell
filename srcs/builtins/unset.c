/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:32:03 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/28 15:53:53 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	unset(char **args, t_env *env)
{
	int		i;
	int		index;
	char	*del_var;

	i = 0;
	while (*args && args[i])
	{
		index = search_in_env(&env->env_var, args[i], ft_strlen(args[i]));
		if (index == -1)
		{
			index = search_in_env(&env->shell_var, args[i], ft_strlen(args[i]));
			if (index == -1)
				return (1);
		}
		del_var = delete_var(env, args[i]);
		i++;
	}
	return (0);
}
