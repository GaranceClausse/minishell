/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 21:36:22 by deacllock         #+#    #+#             */
/*   Updated: 2022/05/08 22:22:38 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_combo	init_combo(t_env *env, t_list *parser, t_lexer *lexer)
{
	t_combo	combo;

	combo.env = env;
	combo.lexer = lexer;
	combo.parser = &parser;
	combo.pid_list = NULL;
	return (combo);
}

static int	exec_pipe(t_combo *combo, t_list *parser, t_list *cur)
{
	t_cmd	*cmd;
	t_cmd	*next;
	int		pipe_fd[2];

	if (pipe(pipe_fd))
		return (wait_all_pids(parser, 1));
	cmd = (t_cmd *)cur->content;
	next = (t_cmd *)cur->next->content;
	cmd->fd_out = pipe_fd[1];
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

	combo = init_combo(env, parser, lexer);
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
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	return (wait_all_pids(parser, ret));
}

// --trace-children=yes --track-fds=<yes
// --child-silent-after-fork=<yes|no>