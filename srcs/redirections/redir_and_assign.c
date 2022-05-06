/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:22:50 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/04 17:44:11 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redirection.h"

int	redir(int *fd_to_change, int new_fd, char *filename)
{
	if (new_fd == -1)
	{
		if (filename)
			perror(filename);
		else
			write(2, "Heredoc error\n", 14);
		return (1);
	}
	if (*fd_to_change > 1)
		close(*fd_to_change);
	*fd_to_change = new_fd;
	return (0);
}

static int	check_and_apply_redir(t_env *env, t_cmd *cmd, t_token *token)
{
	int	fd;

	if (token->type == REDIR_IN)
		return (redir(&(cmd->fd_in),
				open(token->content, O_RDONLY | O_TRUNC), token->content));
	if (token->type == REDIR_OUT)
		return (redir(&(cmd->fd_out), open(token->content, O_CREAT
					| O_WRONLY | O_TRUNC, 0644), token->content));
	if (token->type == HERE_DOC)
	{
		fd = open(TMP, O_CREAT | O_RDWR | O_TRUNC, 0644);
		return (here_doc(env, token->content, fd)
			|| redir(&cmd->fd_in, fd, NULL));
	}
	return (redir(&(cmd->fd_out), open(token->content, O_CREAT
				| O_WRONLY | O_APPEND, 0644), token->content));
}

int	redir_and_assign(t_env *env, t_cmd	*cmd, t_var_list *list)
{
	t_token	*token;
	t_list	*cur;
	char	*var;

	cur = cmd->token_list;
	while (cur)
	{
		token = (t_token *)cur->content;
		if (token->type >= REDIR_IN && token->type <= APPEND)
		{
			if (check_and_apply_redir(env, cmd, token))
				return (1);
		}
		else if (token->type == ASSIGNMENT)
		{
			var = ft_strdup(token->content);
			if (!var)
				return (1);
			if (add_var(env, list, var))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
