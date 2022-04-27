/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:56:43 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/27 14:59:32 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	remove_empties(t_list **list)
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
			break;
	}

	cur = *list;
	while (cur && cur->next)
	{
		token = (t_token *)cur->next->content;
		if (!ft_strcmp(token->content, ""))
		{
			next = cur->next;
			cur->next = cur->next->next;
			delete_token(token);
			free(next);
		}
		cur = cur->next;
	}
}

static int	remove_quotes_from_token(t_token	*token)
{
	char	*tmp;
	char	*start;
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
		if ((token->content[i] == '\'' && !d_quote) || (token->content[i] == '"' && !s_quote))
		{
			tmp = token->content;
			start = ft_substr(token->content, 0, i);
			token->content = ft_strjoin(start, token->content + i + 1);
			free(start);
			free(tmp);
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
		if (remove_quotes_from_token(token))
			return (1);
		cur = cur->next;
	}
	return (0);
}