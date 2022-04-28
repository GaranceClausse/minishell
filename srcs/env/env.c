/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:05:27 by vkrajcov          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/18 16:01:35 by gclausse         ###   ########.fr       */
=======
/*   Updated: 2022/04/28 10:55:44 by vkrajcov         ###   ########.fr       */
>>>>>>> 389b86cfeea02e75acfa317795ee486962150b8e
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "libft.h"

void	free_env(t_env *env)
{
	free_char_tab(env->shell_var.list, 0);
	free_char_tab(env->env_var.list, 0);
}

static t_var_list	*init_var_list(t_var_list *list, int max)
{
	list->size = 0;
	list->max = max;
	list->list = malloc(sizeof(char *) * (max + 1));
	if (!list->list)
		return (NULL);
	list->list[0] = NULL;
	return (list);
}

static t_var_list	*copy_var_list(t_env *env, int max, char *envp[])
{
	int	i;

	if (!init_var_list(&env->env_var, max))
		return (NULL);
	i = 0;
	if (!envp)
		return (&env->env_var);
	while (envp[i])
	{
		if (add_var(env, &env->env_var, ft_strdup(envp[i])))
		{
			free_char_tab(env->env_var.list, 0);
			return (NULL);
		}
		i++;
	}
	return (&env->env_var);
}

t_env	*init_env(t_env *env, int max, char *envp[])
{
	(void)envp;
	env->last_return = 0;
	if (!init_var_list(&env->shell_var, max))
		return (NULL);
	if (!copy_var_list(env, max, envp))
	{
		free_char_tab(env->shell_var.list, 0);
		return (NULL);
	}
	return (env);
}
