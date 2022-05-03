/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:32:03 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/02 16:46:57 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	unset(char **args, t_env *env)
{
	int		i;

	i = 0;
	while (args && args[i])
	{
		if (is_valid_identifier("unset", args[i]))
			return (1);
		free(delete_var(env, args[i++]));
	}
	return (0);
}
