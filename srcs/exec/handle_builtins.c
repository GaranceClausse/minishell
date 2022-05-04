/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:36:55 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 11:56:34 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "exec.h"

int	is_builtin(char *cmd_name, char **builtin_list)
{
	int	i;

	i = 0;
	while (builtin_list[i])
	{
		if (!ft_strcmp(cmd_name, builtin_list[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	exec_builtin(t_env *env, char **word_list, int is_in_pipe)
{
	if (!ft_strcmp(word_list[0], "echo"))
		return (echo(&word_list[1]));
	if (!ft_strcmp(word_list[0], "cd"))
		return (cd(env, &word_list[1]));
	if (!ft_strcmp(word_list[0], "env"))
		return (print_env(env, &word_list[1]));
	if (!ft_strcmp(word_list[0], "pwd"))
		return (pwd(&word_list[1]));
	if (!ft_strcmp(word_list[0], "export"))
		return (export(env, &word_list[1]));
	if (!ft_strcmp(word_list[0], "unset"))
		return(unset(env, &word_list[1]));
	if (!ft_strcmp(word_list[0], "exit"))
		exit_builtin(&word_list[1]);
	return (0);
}