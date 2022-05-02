/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:32:03 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/02 15:43:10 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	unset(char **args, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (args[i][j])
		{
		//	if (ft_isdigit(args[i][0]) || ft_isalnum(args[i][j]) == 0)
		//	{
				ft_printf("export: '%s' : not a valid identifier\n", args[i]);
				return (1);
		//	}
			j++;
		}
		free(delete_var(env, args[i++]));
	}
	return (0);
}
