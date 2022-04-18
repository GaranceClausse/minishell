/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:34:26 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/18 12:01:36 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char *search(t_env *env, char *var)
{
	int	i;
	int	len;
	char	*haystack;

	i = 0;
	len = ft_strlen(var);
	while (env->shell_var.list[i])
	{
		haystack = env->shell_var.list[i];
		if (ft_strncmp(var, haystack, len) == 0)
			return (var);
		i++;
	}
	i = 0;
	while (env->env_var.list[i])
	{
		haystack = env->env_var.list[i];
		if (ft_strncmp(var, haystack, len) == 0)
			return (var);
		i++;
	}
	return (NULL);
}

int	add_var(t_env *env, t_var_list *dst, char *var)
{
	if (search(env, var) != NULL)
		return (0);
	else if (dst->size + 1 > dst->max)
	{
		if (realloc(dst->list, (dst->max * 2 * sizeof(char *))) == NULL)
			return (1);
	}
	dst->list[dst->size] = var;
	dst->list[dst->size + 1] = NULL;
	return (0);
}

int main()
{
	t_env env;
	t_var_list	shell_env;
	
	if (init_env(&env, 5, NULL))
	{
		shell_env = env.shell_var;
		add_var(&env, &shell_env, "coucou=");
		search(&env, "coucou");
		free_env(&env);
	}
}
