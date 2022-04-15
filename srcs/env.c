/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:05:27 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/15 18:29:41 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

//add_var
//delete_var

void	free_var_list(t_var_list *list)
{
	int	i;

	i = 0;
	while (list->list[i])
		free(list->list[i++]);
	free(list);
}

t_var_list *copy_var_list(t_var_list *list, int max, char *envp[])
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
}

t_var_list	*init_var_list(t_var_list *list, int max)
{
	list->size = 0;
	list->max = max;
	list->list = malloc(sizeof(char *) * max);
	if (!list->list)
		return (NULL);
	list[0] = NULL;
	return (list);
}

t_var *env	init_env(t_var *env, int max, char *envp[])
{
	int	i;

	env->last_code = 0;
	if (!init_var_list(&env->shell_var, max))
		return (NULL);
	if (!copy_var_list(&env->env_var, max, envp))
	{
		free_var_list(&env->shell_var);
		return (NULL);
	}
	return (env);
}