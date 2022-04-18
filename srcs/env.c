/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:05:27 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/18 11:48:09 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "libft.h"

void	free_env(t_env *env)
{
	free_char_tab(env->shell_var.list);
	free_char_tab(env->env_var.list);
}

static t_var_list	*init_var_list(t_var_list *list, int max)
{
	list->size = 0;
	list->max = max;
	list->list = malloc(sizeof(char *) * max);
	if (!list->list)
		return (NULL);
	list->list[0] = NULL;
	return (list);
}
/*
static t_var_list *copy_var_list(t_var_list *list, int max, char *envp[])
{
	char	*cur;
	int		i;

	if (!init_var_list(list, max))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		cur = add_var(list, envp[i++]);
		if (!cur)
		{
			free_var_list(list);
			return (NULL);
		}
	}
	return (list);
}*/

t_env	*init_env(t_env *env, int max, char *envp[])
{
	(void)envp;
	env->last_return = 0;
	if (!init_var_list(&env->shell_var, max))
		return (NULL);
	if (!init_var_list(&env->env_var, max))
	{
		free_char_tab(env->shell_var.list);
		return (NULL);
	}
	/*if (!copy_var_list(&env->env_var, max, envp)
	{
		free_var_list(&env->shell_var);
		return (NULL);
	}*/
	return (env);
}
