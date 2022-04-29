/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:51 by vkrajcov          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/29 14:50:48 by gclausse         ###   ########.fr       */
=======
/*   Updated: 2022/04/28 16:49:44 by vkrajcov         ###   ########.fr       */
>>>>>>> 41d31a538110ddf8eee76f19e71cbc80a2afe8d6
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
	if (var[i] != '=')
		return (NULL); 
	return (ft_strdup(&var[i + 1]));
}

char	*get_value(t_env *env, char *value)
{
	int		i;
	i = search_in_env(env->env_var, value, ft_strlen(value));
	if (i > 0)
		return (extract_var_value(env->env_var.list[i]));
	search_in_env(env->shell_var,  value, ft_strlen(value));
	if (i > 0)
		return (extract_var_value(env->shell_var.list[i]));
	return (NULL);
}
