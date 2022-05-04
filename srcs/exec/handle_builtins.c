/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:36:55 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 17:36:20 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo") || !ft_strcmp(cmd_name, "cd")
		|| !ft_strcmp(cmd_name, "env") || !ft_strcmp(cmd_name, "pwd")
		|| !ft_strcmp(cmd_name, "export") || !ft_strcmp(cmd_name, "unset")
		|| !ft_strcmp(cmd_name, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_env *env, char **wordlist)
{
	if (!ft_strcmp(wordlist[0], "echo"))
		return (echo(&wordlist[1]));
	if (!ft_strcmp(wordlist[0], "cd"))
		return (cd(env, &wordlist[1]));
	if (!ft_strcmp(wordlist[0], "env"))
		return (print_env(&env->env_var, &wordlist[1]));
	if (!ft_strcmp(wordlist[0], "pwd"))
		return (pwd(&wordlist[1]));
	if (!ft_strcmp(wordlist[0], "export"))
		return (export(env, &wordlist[1]));
	if (!ft_strcmp(wordlist[0], "unset"))
		return (unset(env, &wordlist[1]));
	if (!ft_strcmp(wordlist[0], "exit"))
		exit_builtin(&wordlist[1]);
	return (0);
}
