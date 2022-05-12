/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_from_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:14:29 by deacllock         #+#    #+#             */
/*   Updated: 2022/05/12 19:10:51 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	move_head_empty_token(t_list **list)
{
	t_token	*token;
	t_list	*cur;

	while (*list)
	{
		token = (t_token *)(*list)->content;
		if (!ft_strcmp(token->content, "") || !ft_strcmp(token->content, "\1\1"))
		{
			cur = (*list);
			*list = (*list)->next;
			delete_token(token);
			free(cur);
		}
		else
			break ;
	}
}

void	remove_empty_tokens(t_list **list)
{
	t_list	*cur;
	t_list	*next;
	t_token	*token;

	move_head_empty_token(list);
	cur = *list;
	while (cur && cur->next)
	{
		token = (t_token *)cur->next->content;
		while (cur->next && (!ft_strcmp(token->content, "")
				|| !ft_strcmp(token->content, "\1\1")))
		{
			next = cur->next;
			cur->next = cur->next->next;
			delete_token(token);
			free(next);
			if (cur->next)
				token = (t_token *)cur->next->content;
		}
		cur = cur->next;
	}
}

static void	move_head_empty_cmds(t_list **list)
{
	t_list	*cur;
	t_cmd	*cmd;

	while (*list)
	{
		cmd = (t_cmd *)(*list)->content;
		if (!cmd->token_list && !cmd->wordlist)
		{
			cur = (*list);
			*list = (*list)->next;
			free(cmd);
			free(cur);
		}
		else
			break ;
	}
}

void	remove_empty_cmds(t_list **list)
{
	t_list	*cur;
	t_list	*next;
	t_cmd	*cmd;

	move_head_empty_cmds(list);
	cur = *list;
	while (cur && cur->next)
	{
		cmd = (t_cmd *)cur->next->content;
		while (cur->next && !cmd->token_list && !cmd->wordlist)
		{
			next = cur->next;
			cur->next = cur->next->next;
			free(cmd);
			free(next);
			if (cur->next)
				cmd = (t_cmd *)cur->next->content;
		}
		cur = cur->next;
	}
}
