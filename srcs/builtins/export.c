/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:12:16 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/29 15:49:22 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_export(char **args, t_var_list *env_var)
{
	int		i;
	char	*var_value;
	char	*var_name;

	i = 0;
	while (env_var->list[i])
	{
		var_value = extract_var_value(env_var->list[i]);
		var_name = extract_name(env_var->list[i]);
		write(1, "export ", 8);
		write (1, var_name, ft_strlen(var_name));
		write(1, "=\"", 2);
		write (1, var_value, ft_strlen(var_value));
		write (1, "\"\n", 2);
		free(var_value);
		free(var_name);
		i++;
	}
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
		print_export(args, &env->env_var);
	while (*args && args[i])
	{
		j = 0;
		var_name = extract_name(args[i]);
		while (var_name[j])
		{
			if (ft_isalnum(var_name[j]) == 0)
			{
				write(2, "export: '", 10);
				write(2, args[i], ft_strlen(args[i]));
				write (2, "' : not a valid identifier", 27);
				free(var_name);
				return (1);
			}
			j++;
		}
		index = search_in_env(&env->env_var, var_name, ft_strlen(args[i]));
		var_value = extract_var_value(args[i]);
		var = ft_strjoin3(var_name, "=", var_value);
		if (index == -1)
		{		
			if (!var_value)
				var_value = ft_strdup("''");	
			add_var(env, &env->env_var, var);
			print_export(&args[1], &env->env_var);
			
		}
		else
		{
			if (var_value)
				change_var(&env->env_var, args[i]);
			print_export(&args[1], &env->env_var);
		}
		free(var_value);
		free(var);
		i++;
	}


}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc != 0)
	{
		init_env(&env, 10, envp);
		export(&argv[1], &env);
	}
	return (0);
}