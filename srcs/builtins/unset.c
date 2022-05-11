/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:32:03 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/11 22:36:42 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	unset_identifier(char *str, char *arg)
{
	int		i;
	int		pbm;
	char	*msg;

	i = 0;
	pbm = 0;
	while (arg[i])
	{
		if ((ft_isalnum(arg[i]) && ft_isdigit(arg[i])
				&& ft_isunderscore(arg[i])) || ft_isdigit(arg[0]) == 0
			|| arg[i] == '=')
					pbm++;
		i++;
	}
	if (pbm != 0 || !ft_strcmp(arg, ""))
	{
		msg = ft_strjoin3(str, ": '", arg);
		if (!msg)
			return (1);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		free(msg);
		return (1);
	}
	return (0);
}

int	unset(t_env *env, char **args)
{
	int		i;

	i = 0;
	while (args && args[i])
	{
		if (unset_identifier("unset", args[i]))
			return (1);
		free(delete_var(env, args[i++]));
	}
	return (0);
}
