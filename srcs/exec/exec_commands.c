/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 21:36:22 by deacllock         #+#    #+#             */
/*   Updated: 2022/05/12 18:52:36 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	exec_pipe(t_combo *combo, t_list *parser, t_list *cur)
{
	t_cmd	*cmd;
	t_cmd	*next;
	int		pipe_fd[2];

	if (pipe(pipe_fd))
		return (wait_all_pids(parser, 1));
	cmd = (t_cmd *)cur->content;
	next = (t_cmd *)cur->next->content;
	if (cmd->fd_out == 1)
		cmd->fd_out = pipe_fd[1];
	else
		close(pipe_fd[1]);
	if (next->fd_in == 0)
		next->fd_in = pipe_fd[0];
	if (fork_and_exec(combo, cmd))
		return (wait_all_pids(parser, 1));
	close_fds(cmd->fd_in, cmd->fd_out);
	return (0);
}

int	exec_commands(t_env *env, t_list *parser, t_lexer *lexer)
{
	t_combo	combo;
	t_cmd	*cmd;
	t_list	*cur;
	int		ret;

	combo = init_combo(env, &parser, lexer);
	if (!ft_lstlen(parser))
		return (1);
	cur = parser;
	while (cur && cur->next)
	{
		if (exec_pipe(&combo, parser, cur))
			return (1);
		cur = cur->next;
	}
	cmd = (t_cmd *)cur->content;
	if (shall_i_fork(cmd))
		ret = fork_and_exec(&combo, cmd);
	else
		ret = exec_or_assign_only(&combo, cmd);
	if (cmd->fd_in != 0 && cmd->fd_in != -1)
		close(cmd->fd_in);
	return (wait_all_pids(parser, ret));
}

static void	launch_exec(t_combo *combo, char **wordlist, char *cmd_name)
{
	delete_parser(combo->parser);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(wordlist[0], wordlist, combo->env->env_var.list);
	close(0);
	close(1);
	if (errno == 2 || errno == 13)
		command_not_found(combo, wordlist, cmd_name);
	perror(cmd_name);
	free(cmd_name);
	free_before_exit(combo, wordlist);
}

int	exec(t_combo *combo, t_cmd *cmd)
{
	char	**wordlist;
	char	*cmd_name;

	wordlist = get_wordlist(combo, cmd);
	if (!wordlist)
		return (1);
	if (is_builtin(wordlist[0]))
		return (handle_builtins(combo, cmd, wordlist));
	cmd_name = ft_strdup(wordlist[0]);
	if (!cmd_name)
	{
		free_before_exit(combo, wordlist);
		exit(1);
	}
	if (ft_strlen(cmd_name) && !ft_is_in_set(cmd_name[0], "/.\0"))
	{
		if (get_cmd_name(combo->env, wordlist))
		{
			free_before_exit(combo, wordlist);
			exit(1);
		}
		command_not_found(combo, wordlist, cmd_name);
	}
	launch_exec(combo, wordlist, cmd_name);
	exit(1);
}
