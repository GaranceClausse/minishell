/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:22:50 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/03 14:50:15 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"

int	redir(int *fd_to_change, int new_fd)
{
	if (new_fd == -1)
		return (1);
	if (*fd_to_change != -1)
		close(*fd_to_change);
	*fd_to_change = new_fd;
	return (0);
}

int	check_and_apply_redir(t_env *env, t_cmd *cmd, t_token *token)
{
	(void)env;

	if (token->type == REDIR_IN)
		return (redir(&(cmd->fd_in),
				open(token->content, O_RDONLY | O_TRUNC)));
	if (token->type == REDIR_OUT)
		return (redir(&(cmd->fd_out),
				open(token->content, O_CREAT | O_WRONLY | O_TRUNC, 0644)));
	/*if (token->type == HERE_DOC)
	{
		fd = open("/tmp", __O_TMPFILE | O_RDWR | O_APPEND);
		if (here_doc(env, token->content, fd) || redir(&cmd->fd_in, fd))
			return (1);
	}*/
	return (redir(&(cmd->fd_out),
			open(token->content, O_CREAT | O_WRONLY | O_APPEND, 0644)));
}

int	redir_and_assign(t_env *env, t_cmd	*cmd)
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
		else if (token->type == ASSIGNMENT)
		{
			if (add_var(env, &env->shell_var, token->content))
				return (1);
		}
		else
		{
			write(2, "Error\n", 6);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}