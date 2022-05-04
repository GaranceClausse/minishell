/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:22:16 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 15:12:34 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void free_before_exit(t_env *env, t_cmd *cmd, char **wordlist)
{
	(void)cmd;
	(void)env;
	free_char_tab(wordlist, 0);
}

int	command_not_found(t_env *env, t_cmd *cmd, char **wordlist)
{
	char	*msg;

	msg = ft_strjoin(wordlist[0], " : command not found\n");
	if (!msg)
		return (1);
	write(2, msg, ft_strlen(msg));
	free(msg);
	free_before_exit(env, cmd, wordlist);
	return (127);
}

//creer fct pour free toutes les structures
int	exec(t_env *env, t_cmd *cmd)
{
	char	**wordlist;
	char	*cmd_name;
	int		ret;

	wordlist = token_to_wordlist(cmd->wordlist);
	if (!wordlist)
		return (1);
	if (is_builtin(wordlist[0]))
	{
		ret = exec_builtin(env, wordlist);
		free_before_exit(env, cmd, wordlist);
		if (cmd->is_in_pipe)
			exit(ret);
		return (ret);
	}
	if (wordlist[0][0] != '/')
	{
		cmd_name = get_cmd_name(env, wordlist[0]);
		if (!cmd_name)
			exit(command_not_found(env, cmd, wordlist));
		free(wordlist[0]);
		wordlist[0] = cmd_name;
	}
	execve(wordlist[0], wordlist, env->env_var.list);
	free_before_exit(env, cmd, wordlist); //handle command not found
	exit(1);
}

int	redir_assign_exec(t_env *env, t_cmd *cmd)
{
	int	oldin;
	int	oldout;
	int	ret;

	if (redir_and_assign(env, cmd))
	{
		//free_before_exit()
		return (1);
	}
	oldin = dup(STDIN_FILENO);
	oldout = dup(STDOUT_FILENO);
	dup2(cmd->fd_in, STDIN_FILENO); //check?
	dup2(cmd->fd_out, STDOUT_FILENO);
	ret = exec(env, cmd);
	dup2(STDIN_FILENO, oldin);
	dup2(STDOUT_FILENO, oldout);
	return (ret);
}