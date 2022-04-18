/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:34:26 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/18 15:42:55 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	search(t_var_list *dst, char *var_name)
{
	int	i;
	int	len;
	char	*ret;

	i = 0;
	len = ft_strlen(var_name);
	while (dst->list[i])
	{
		ret = dst->list[i];
		if (ft_strncmp(var_name, ret, len) == 0)
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
/* -1 == all good;
   0 == error;
   1 == not finished;
   comme ca add_var return +1 quand c'est fini ou error */
int	change_var(t_var_list *dst, char *var)
{
	char	*var_name;
	int	index;

	var_name = extract_name(var);
	if (var_name == NULL)
		return (0);
	index = search(dst, var_name);
	free(var_name);
	if (index != -1)
	{
		free(dst->list[index]);
		dst->list[index] = var;
		return (-1);
	}
	return (1);
}

int	add_var(t_env *env, t_var_list *dst, char *var)
{
	int	ret;

	ret = change_var(&env->shell_var, var);
	if (ret != 1)
		return (ret + 1);
	ret = change_var(&env->env_var, var);
	if (ret != 1)
		return (ret + 1);
	else if (dst->size + 1 > dst->max)
	{
		dst->max *= 2;
		dst->list = realloc_str(dst->list, (dst->max * 2 + 1));
		if (!dst->list)
			return (1);
	}
	dst->list[dst->size++] = var;
	dst->list[dst->size] = NULL;
	return (0);
}

char	*delete_var(t_env *env, char *var_name)
{
	int	index;
	t_var_list	*var_list;
	char	*tmp;

	index = search(&env->shell_var, var_name);
	if (index == -1)
	{
		index = search(&env->env_var, var_name);
		var_list = &env->env_var;
		if (index == -1)
			return (NULL);
	}
	else
		var_list = &env->shell_var;
	tmp = var_list->list[index];
	while (index + 1 <= var_list->size)
	{
		var_list->list[index] = var_list->list[index + 1];
		index++;
	}
	var_list->size -= 1;
	return (tmp);
}
