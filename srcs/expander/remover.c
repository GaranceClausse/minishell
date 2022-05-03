/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:56:43 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/03 12:02:46 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	remove_empty_tokens(t_list **list)
{
	t_list	*cur;
	t_list	*next;
	t_token	*token;

	while (*list)
	{
		token = (t_token *)(*list)->content;
		if (!ft_strcmp(token->content, ""))
		{
			cur = (*list);
			*list = (*list)->next;
			delete_token(token);
			free(cur);
		}
		else
			break ;
	}
	cur = *list;
	while (cur && cur->next)
	{
		token = (t_token *)cur->next->content;
		while (cur->next && !ft_strcmp(token->content, ""))
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

void	remove_empty_cmds(t_list **list)
{
	t_list	*cur;
	t_list	*next;
	t_cmd	*cmd;

	while (*list)
	{
		cmd = (t_cmd *)(*list)->content;
		if (!cmd->token_list && !cmd->word_list)
		{
			cur = (*list);
			*list = (*list)->next;
			free(cmd);
			free(cur);
		}
		else
			break;
	}

	cur = *list;
	while (cur && cur->next)
	{
		cmd = (t_cmd *)cur->next->content;
		while (cur->next && !cmd->token_list && !cmd->word_list)
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

void	delete_quotes_token(t_token *token, int i)
{
	char	*tmp;
	char	*start;

	tmp = token->content;
	start = ft_substr(token->content, 0, i);
	token->content = ft_strjoin(start, token->content + i + 1);
	free(start);
	free(tmp);
}

static int	remove_quotes_from_token(t_token	*token)
{
	int		s_quote;
	int		d_quote;
	int		i;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (token->content[i])
	{
		if (token->content[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (token->content[i] == '"' && !s_quote)
			d_quote = !d_quote;
		if ((token->content[i] == '\'' && !d_quote)
			|| (token->content[i] == '"' && !s_quote))
		{
			delete_quotes_token(token, i);
			if (!token->content)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	remove_quotes(t_list **list)
{
	t_list	*cur;
	t_token	*token;

	cur = *list;
	while (cur)
	{
		token = cur->content;
		if (token->type != HERE_DOC)
		{
			if (remove_quotes_from_token(token))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
