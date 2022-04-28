/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:51 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/28 11:50:22 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	search_in_env(t_var_list *dst, char *var_name, int len)
{
	int		i;
	char	*ret;

	i = 0;
	while (dst->list[i])
	{
		ret = dst->list[i];
		if (ft_strncmp(var_name, ret, len) == 0
			&& ret[len] && ret[len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (ft_substr(var, 0, i));
}

char	*extract_var_value(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (ft_strdup(&var[i + 1]));
}
