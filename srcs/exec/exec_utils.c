/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:22:16 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/12 13:27:10 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_combo	init_combo(t_env *env, t_list **parser, t_lexer *lexer)
{
	t_combo	combo;

	combo.env = env;
	combo.lexer = lexer;
	combo.parser = parser;
	combo.pid_list = NULL;
	return (combo);
}

void	free_before_exit(t_combo *combo, char **wordlist)
{
	free_env(combo->env);
	delete_parser(combo->parser);
	free_lexer(combo->lexer);
	if (wordlist)
		free_char_tab(wordlist, 0);
}

void	command_not_found(t_combo *combo, char **wordlist, char *cmd_name)
{
	char	*msg;

	msg = ft_strjoin(cmd_name, ": Command not found\n");
	free_before_exit(combo, wordlist);
	free(cmd_name);
	ft_putstr_fd(msg, 2);
	free(msg);
	exit(127);
}

int	assign_exec(t_combo *combo, t_cmd *cmd)
{
	int	ret;
	int	oldin;
	int	oldout;

	if (assign(combo->env, cmd, &combo->env->env_var)
		|| cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		if (cmd->is_in_pipe)
		{
			free_before_exit(combo, NULL);
			exit(1);
		}
		return (1);
	}
	if (!cmd->is_in_pipe)
		save_fd(cmd, &oldin, &oldout);
	if (cmd->fd_in != 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	ret = exec(combo, cmd);
	if (!cmd->is_in_pipe)
		restore_fd(cmd, oldin, oldout);
	return (ret);
}

int	exec_or_assign_only(t_combo *combo, t_cmd *cmd)
{
	if (ft_lstlen(cmd->wordlist))
		return (assign_exec(combo, cmd));
	else
		return (assign(combo->env, cmd, &combo->env->shell_var));
	return (0);
}
