/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:22:16 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/09 15:41:39 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_before_exit(t_combo *combo, char **wordlist)
{
	free_env(combo->env);
	delete_parser(combo->parser);
	free_lexer(combo->lexer);
	if (wordlist)
		free_char_tab(wordlist, 0);
}

// 126 etc...
static int	exec(t_combo *combo, t_cmd *cmd)
{
	char	**wordlist;

	wordlist = get_wordlist(combo, cmd);
	if (!wordlist)
		return (1);
	if (is_builtin(wordlist[0]))
		return (handle_builtins(combo, cmd, wordlist));
	if (wordlist[0][0] != '/' && wordlist[0][0] != '\0')
	{
		if (get_cmd_name(combo->env, wordlist))
		{
			free_before_exit(combo, wordlist);
			exit(1);
		}
	}
	delete_parser(combo->parser);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(wordlist[0], wordlist, combo->env->env_var.list);
	perror(wordlist[0]);
	free_before_exit(combo, wordlist);
	if (errno == 2)
		exit(127);
	exit(1);
}

int	assign_exec(t_combo *combo, t_cmd *cmd)
{
	int	oldin;
	int	oldout;
	int	ret;

	if (assign(combo->env, cmd, &combo->env->env_var))
	{
		if (cmd->is_in_pipe)
			free_before_exit(combo, NULL);
		return (1);
	}
	oldin = dup(STDIN_FILENO);
	oldout = dup(STDOUT_FILENO);
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	ret = exec(combo, cmd);
	dup2(STDIN_FILENO, oldin);
	dup2(STDOUT_FILENO, oldout);
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
