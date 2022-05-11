/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:22:50 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/11 15:13:50 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redirection.h"

static int	apply_redir(int *fd_to_change, int new_fd, char *filename)
{
	if (*fd_to_change != 1 && *fd_to_change != 0 && *fd_to_change != -1)
		close(*fd_to_change);
	*fd_to_change = new_fd;
	if (new_fd == -1)
	{
		if (filename)
			perror(filename);
		else
			ft_putstr_fd("Heredoc error\n", 2);
		return (1);
	}
	*fd_to_change = new_fd;
	return (0);
}

static int	check_and_apply_redir(t_env *env, t_cmd *cmd, t_token *token)
{
	int	fds[2];

	if (token->type == REDIR_IN)
		return (apply_redir(&(cmd->fd_in),
				open(token->content, O_RDONLY), token->content));
	if (token->type == REDIR_OUT)
		return (apply_redir(&(cmd->fd_out), open(token->content, O_CREAT
					| O_WRONLY | O_TRUNC, 0644), token->content));
	if (token->type == HERE_DOC)
	{
		if (pipe(fds))
			return (1);
		if (here_doc(env, token->content, fds[1]))
		{
			close_fds(fds[0], fds[1]);
			return (1);
		}
		close(fds[1]);
		return (apply_redir(&(cmd->fd_in), fds[0], NULL));
	}
	return (apply_redir(&(cmd->fd_out), open(token->content, O_CREAT
				| O_WRONLY | O_APPEND, 0644), token->content));
}

int	redir(t_env *env, t_cmd	*cmd)
{
	t_token	*token;
	t_list	*cur;

	cur = cmd->token_list;
	while (cur)
	{
		token = (t_token *)cur->content;
		if (token->type >= REDIR_IN && token->type <= APPEND)
		{
			if (check_and_apply_redir(env, cmd, token))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	assign(t_env *env, t_cmd *cmd, t_var_list *list)
{
	t_token	*token;
	t_list	*cur;
	char	*var;

	cur = cmd->token_list;
	while (cur)
	{
		token = (t_token *)cur->content;
		if (token->type == ASSIGNMENT)
		{
			var = ft_strdup(token->content);
			if (!var)
				return (1);
			if (is_valid_identifier("assign", var))
			{
				free(var);
				return (1);
			}
			if (add_var(env, list, var))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
