/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 20:15:44 by deacllock         #+#    #+#             */
/*   Updated: 2022/05/10 15:37:23 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>
#include <sys/types.h>

static int	print_sig_interrupt(int signum)
{
	
	if (signum == SIGQUIT)
		write(2, "Quit (core dumped)", 19);
	write(1, "\n", 1);
	return (signum + 128);
}

int	wait_all_pids(t_list *parser, int ret)
{
	t_cmd	*cmd;
	int		wstatus;

	wstatus = 0;
	while (parser)
	{
		cmd = (t_cmd *)parser->content;
		if (cmd->pid != -1)
			waitpid(cmd->pid, &wstatus, 0);
		parser = parser->next;
	}
	if (ret)
		return (ret);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		return (print_sig_interrupt(WTERMSIG(wstatus)));
	return (EXIT_FAILURE);
}

int	shall_i_fork(t_cmd	*cmd)
{
	t_token	*token;

	if (!cmd->is_in_pipe)
	{
		if (!cmd->wordlist)
			return (0);
		token = (t_token *)cmd->wordlist->content;
		if (is_builtin(token->content))
			return (0);
		cmd->is_in_pipe = 1;
	}
	return (1);
}

int	fork_and_exec(t_combo *combo, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (!(cmd->pid))
		return (exec_or_assign_only(combo, cmd));
	return (0);
}
