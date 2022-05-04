/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:22:16 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 16:44:40 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void free_before_exit(t_combo *combo, char **wordlist)
{
	free_env(combo->env);
	delete_parser(combo->parser);
	free_lexer(combo->lexer);
	if (wordlist)
		free_char_tab(wordlist, 0);
}

int	command_not_found(t_combo *combo, char **wordlist)
{
	char	*msg;

	msg = ft_strjoin(wordlist[0], " : command not found\n");
	if (!msg)
		return (1);
	write(2, msg, ft_strlen(msg));
	free(msg);
	free_before_exit(combo, wordlist);
	return (127);
}

//creer fct pour free toutes les structures
static int	exec(t_combo *combo, t_cmd *cmd)
{
	char	**wordlist;
	char	*cmd_name;
	int		ret;

	wordlist = token_to_wordlist(cmd->wordlist);
	if (!wordlist)
		return (1);
	if (is_builtin(wordlist[0]))
	{
		ret = exec_builtin(combo->env, wordlist);
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
		if (!cmd_name)
			exit(command_not_found(combo, wordlist));
		free(wordlist[0]);
		wordlist[0] = cmd_name;
	}
	execve(wordlist[0], wordlist, combo->env->env_var.list);
	free_before_exit(combo, wordlist); //handle command not found
	exit(1);
}

int	redir_assign_exec(t_combo *combo, t_cmd *cmd)
{
	int	oldin;
	int	oldout;
	int	ret;

	if (redir_and_assign(combo->env, cmd, &combo->env->env_var))
	{
		//free_before_exit(combo, NULL);
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

int exec_commands(t_env *env, t_list **parser, t_lexer *lexer)
{
	t_combo combo;
	t_list	*cur;
	t_cmd	*cmd;

	combo.env = env;
	combo.lexer = lexer;
	combo.parser = parser;
	cur = *parser;
	while (cur)
	{
		cmd = (t_cmd *)cur->content;
		if (ft_lstlen(cmd->wordlist))
		{
			if (redir_assign_exec(&combo, cmd))
				return (1);
		}
		else
		{
			if(redir_and_assign(env, cmd, &env->shell_var))
				return (1);// check output toussa
		}
		cur = cur->next;
	}
	return (0);
}