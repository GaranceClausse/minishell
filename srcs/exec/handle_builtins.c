/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:36:55 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/08 21:39:18 by deacllock        ###   ########.fr       */
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

static int	exec_builtin(t_combo *combo, char **wordlist)
{
	if (!ft_strcmp(wordlist[0], "echo"))
		return (echo(&wordlist[1]));
	if (!ft_strcmp(wordlist[0], "cd"))
		return (cd(combo->env, &wordlist[1]));
	if (!ft_strcmp(wordlist[0], "env"))
		return (print_env(&combo->env->env_var, &wordlist[1]));
	if (!ft_strcmp(wordlist[0], "pwd"))
		return (pwd(&wordlist[1]));
	if (!ft_strcmp(wordlist[0], "export"))
		return (export(combo->env, &wordlist[1]));
	if (!ft_strcmp(wordlist[0], "unset"))
		return (unset(combo->env, &wordlist[1]));
	if (!ft_strcmp(wordlist[0], "exit"))
		exit_builtin(combo, &wordlist[1]);
	return (0);
}

int	handle_builtins(t_combo *combo, t_cmd *cmd, char **wordlist)
{
	int	ret;

	ret = exec_builtin(combo, wordlist);
	if (cmd->is_in_pipe)
	{
		free_before_exit(combo, wordlist);
		exit(ret);
	}
	free_char_tab(wordlist, 0);
	//unset all vars 
	return (ret);
}
