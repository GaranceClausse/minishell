/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:07:30 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/11 14:17:23 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_env(t_var_list *env_var, char **args)
{
	int	i;

	i = 0;
	if (*args)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	while (env_var->list[i])
	{
		if (ft_strchr(env_var->list[i], '='))
			printf("%s\n", env_var->list[i]);
		i++;
	}
	return (0);
}
