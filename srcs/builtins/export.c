/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:12:16 by gclausse          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/02 11:51:06 by vkrajcov         ###   ########.fr       */
=======
/*   Updated: 2022/05/02 11:59:00 by gclausse         ###   ########.fr       */
>>>>>>> fce29068110ec1c91bdebd9db4362898f504c883
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**order_list(t_var_list *env_var)
{
	char	**order_env;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	order_env = malloc(sizeof(char *) * (env_var->size + 1));
	while (env_var->list[i])
	{
		order_env[i] = ft_strdup(env_var->list[i]);
		i++;
	}
	i = 0;
	while (i < env_var->size)
	{
		j = i + 1;
		while (order_env[j])
		{
			if (ft_strcmp(order_env[i], order_env[j]) > 0)
			{
				tmp = order_env[i];
				order_env[i] = order_env[j];
				order_env[j] = tmp;
			}
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
		var_value = extract_var_value(env_list[i]);
		var_name = extract_name(env_list[i]);
		if (!var_value)
			ft_printf("export %s\n", var_name);
		else if (ft_strcmp(var_value, "\"\"") == 0)
			 ft_printf("export %s=\"\"\n", var_name);
		else
			ft_printf("export %s=\"%s\"\n", var_name, var_value);
		free(var_value);
		free(var_name);
		i++;
	}
	free_char_tab(env_list, 0);
	return (0);
}

int	export(char **args, t_env *env)
{
	int		i;
	int		j;
	int		index;
	char	*var;
	char	*var_name;
	char	*var_value;

	i = 0;
	if (!*args)
		print_export(&env->env_var);
	while (*args && args[i])
	{
		j = 0;
		var_name = extract_name(args[i]);
		while (var_name[j])
		{
			if (ft_isalnum(var_name[j]) == 0)
			{
				ft_printf("export: '%s' : not a valid identifier", args[i]);
				free(var_name);
				return (1);
			}
			j++;
		}
		index = search_in_env(&env->env_var, var_name, ft_strlen(var_name));
		var_value = extract_var_value(args[i]);
		if (index == -1 && args[i][ft_strlen(args[i]) - 1] && args[i][ft_strlen(args[i]) - 1] != '=')
			add_var(env, &env->env_var, args[i]);
		else if (index == -1)
		{		
			if (!var_value)
				var_value = ft_strdup("\"\"");
			var = ft_strjoin3(var_name, "=", var_value);
			add_var(env, &env->env_var, var);
		}
		else
		{
			if (!var_value)
				var_value = ft_strdup("\"\"");
			var = ft_strjoin3(var_name, "=", var_value);
			change_var(&env->env_var, var);
		}
		if (var_value)
			free(var_value);
		free(var_name);
		i++;
	}
	print_export(&env->env_var);
	return (0);
}

/*
int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc != 0)
	{
		init_env(&env, 10, envp);
		export(&argv[1], &env);
	}
	return (0);
}*/
