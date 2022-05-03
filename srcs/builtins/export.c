/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:12:16 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/03 16:50:54 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**order_list(t_var_list *env_var)
{
	char	**order_env;
	int		i;
	int		j;

	i = -1;
	order_env = malloc(sizeof(char *) * (env_var->size + 1));
	if (!order_env)
		return (NULL);
	while (env_var->list[++i])
		order_env[i] = ft_strdup(env_var->list[i]);
	i = 0;
	while (i < env_var->size)
	{
		j = i + 1;
		while (j < env_var->size && order_env[j])
		{
			if (ft_strcmp(order_env[i], order_env[j]) > 0)
				ft_swap_ptr((void **)&order_env[i], (void **)&order_env[j]);
			j++;
		}
		i++;
	}
	order_env[i] = NULL;
	return (order_env);
}

int	print_export(t_var_list *env_var)
{
	int		i;
	char	*var_value;
	char	*var_name;
	char	**env_list;

	i = 0;
	env_list = order_list(env_var);
	while (env_list[i])
	{		
		var_name = extract_name(env_list[i]);
		if (ft_strchr(env_list[i], '=') == 0)
			printf("export %s\n", var_name);
		else
		{
			var_value = extract_var_value(env_list[i]);
			printf("export %s=\"%s\"\n", var_name, var_value);
			free(var_value);
		}
		free(var_name);
		i++;
	}
	free_char_tab(env_list, 0);
	return (0);
}

char	*exported_var(char *arg)
{
	char	*var_name;
	char	*var_value;
	char	*var;

	var_name = extract_name(arg);
	var_value = extract_var_value(arg);
	var = ft_strdup(arg);
	if (ft_strchr(arg, '='))
	{
		free(var);
		var = ft_strjoin3(var_name, "=", var_value);
	}
	free(var_value);
	free(var_name);
	return (var);
}

int	export(char **args, t_env *env)
{
	int		i;
	char	*var;

	i = 0;
	if (!*args)
		print_export(&env->env_var);
	while (args[i])
	{
		if (is_valid_identifier("export", args[i]) == 1)
			return (1);
		var = exported_var(args[i]);
		add_var(env, &env->env_var, var);
		i++;
	}
	return (0);
}
