/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:05:27 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/12 15:21:59 by gclausse         ###   ########.fr       */
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

static int	handle_shlvl(t_env *env)
{
	char	*var_value;
	int		nb;
	char	*var;

	var_value = get_value(env, "SHLVL");
	if (!var_value)
		return (1);
	nb = ft_atoi(var_value) + 1;
	free(var_value);
	var_value = ft_itoa(nb);
	var = ft_strjoin("SHLVL=", var_value);
	free(var_value);
	return (add_var(env, &env->env_var, var));
}

static t_var_list	*copy_var_list(t_env *env, int max, char *envp[])
{
	int		i;

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
	if (handle_shlvl(env))
	{
		free_char_tab(env->env_var.list, 0);
		return (NULL);
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
