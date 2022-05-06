/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:22:16 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 17:45:04 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	g_last_return;
void	free_before_exit(t_combo *combo, char **wordlist)
{
	free_env(combo->env);
	delete_parser(combo->parser);
	free_lexer(combo->lexer);
	if (wordlist)
		free_char_tab(wordlist, 0);
	ft_lstclear(&combo->pid_list, free);
}

int	command_not_found(t_combo *combo, char **wordlist)
{
	char	*msg;

	msg = ft_strjoin(wordlist[0], " : command not found\n");
	free_before_exit(combo, wordlist);
	if (!msg)
		return (1);
	write(2, msg, ft_strlen(msg));
	free(msg);
	return (127);
}

//creer fct pour free toutes les structures
static int	exec(t_combo *combo, t_cmd *cmd)
{
	char	**wordlist;
	char	*cmd_name;
	int		ret;
	int		is_in_pipe;

	wordlist = token_to_wordlist(cmd->wordlist);
	is_in_pipe = cmd->is_in_pipe;
	if (!wordlist) //you not freiing
		return (1);
	if (is_builtin(wordlist[0]))
	{
		ret = exec_builtin(combo, wordlist);	
		if (cmd->is_in_pipe)
		{
			free_before_exit(combo, wordlist);
			exit(ret);
		}
		free_char_tab(wordlist, 0); //do we want to unset?make 
		return (ret);
	}
	if (wordlist[0][0] != '/')
	{
		cmd_name = get_cmd_name(combo->env, wordlist[0]);
		if (cmd_name)
		{
			//exit(command_not_found(combo, wordlist));
			free(wordlist[0]);
			wordlist[0] = cmd_name;
		}		
	}
	execve(wordlist[0], wordlist, combo->env->env_var.list);
	perror(wordlist[0]);
	free_before_exit(combo, wordlist); //handle command not found
	if (errno == 2)
		exit(127);
	exit(1);
}

int	redir_assign_exec(t_combo *combo, t_cmd *cmd)
{
	int	oldin;
	int	oldout;
	int	ret;

	if (redir_and_assign(combo->env, cmd, &combo->env->env_var)) // check bien ce truc
	{
		// free_before_exit(combo, NULL);
		return (1);
	}
	oldin = dup(STDIN_FILENO);
	oldout = dup(STDOUT_FILENO);
	dup2(cmd->fd_in, STDIN_FILENO); //check?
	dup2(cmd->fd_out, STDOUT_FILENO);
	ret = exec(combo, cmd);
	dup2(STDIN_FILENO, oldin);
	dup2(STDOUT_FILENO, oldout);
	return (ret);
}

int	exec_or_assign_only(t_combo *combo, t_cmd *cmd)
{
	if (ft_lstlen(cmd->wordlist))
		return (redir_assign_exec(combo, cmd));
	else
		return (redir_and_assign(combo->env, cmd, &combo->env->shell_var));
	return (0);
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
	}
	return (1);
}

int fork_and_exec(t_combo *combo, t_cmd *cmd)
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t));
	if (!pid)
		return (1);
	*pid = fork(); //stock and check

	if (add_pid(&combo->pid_list, pid) || *pid == -1)
		return (wait_and_del_pid(combo->pid_list, 1));
	if (!(*pid))
		return (exec_or_assign_only(combo, cmd));
	return (0);
}

//get return
int exec_commands(t_env *env, t_list *parser, t_lexer *lexer)
{
	t_combo combo;
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		ret;
	t_list	*cur;

	combo.env = env;
	combo.lexer = lexer;
	combo.parser = &parser;
	combo.pid_list = NULL;
	if (ft_lstlen(parser))
	{
		cur = parser;
		while (cur && cur->next)
		{
			if (pipe(pipe_fd))
				return (wait_and_del_pid(combo.pid_list, 1));
			cmd = (t_cmd *)cur->content;
			cmd->fd_out = pipe_fd[1];
			if (fork_and_exec(&combo, cmd))
				return (wait_and_del_pid(combo.pid_list, 1));
			if (cmd->fd_in)
				close(cmd->fd_in);
			if (cmd->fd_out != 1)
				close(cmd->fd_out);
			cur = cur->next;
			cmd = (t_cmd *)cur->content;
			cmd->fd_in = pipe_fd[0];
		}
		cmd = (t_cmd *)cur->content;
		if (shall_i_fork(cmd))
		{
			ret = fork_and_exec(&combo, cmd);
			return (wait_and_del_pid(combo.pid_list, ret));
		}
		if (exec_or_assign_only(&combo, cmd))
			return (wait_and_del_pid(combo.pid_list, 1));
		return (wait_and_del_pid(combo.pid_list, 0));
	}
	return (0);
}

// --trace-children=yes --track-fds=<yes
// --child-silent-after-fork=<yes|no>