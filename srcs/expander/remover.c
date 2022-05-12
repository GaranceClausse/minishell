/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:56:43 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/12 20:26:00 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	delete_quotes_token(t_token *token, int i)
{
	char	*tmp;
	char	*start;

	tmp = token->content;
	start = ft_substr(token->content, 0, i);
	if (token->content + i + 1)
	{
		token->content = ft_strjoin(start, token->content + i + 1);
		free(start);
	}
	else
		token->content = start;
	free(tmp);
}

static int	remove_quotes_content(t_token *token, int *quotes, int *i)
{
	if (token->content[*i] == '\'' && !quotes[1] && !quotes[2])
		quotes[0] = !quotes[0];
	else if (token->content[*i] == '"' && !quotes[0] && !quotes[2])
		quotes[1] = !quotes[1];
	if ((token->content[*i] == '\'' && !quotes[1] && !quotes[2])
		|| (token->content[*i] == '"' && !quotes[0] && !quotes[2]))
	{
		delete_quotes_token(token, *i);
		if (!token->content)
			return (1);
	}
	else
		(*i)++;
	return (0);
}

/*
quotes[0] = s_quotes
quotes[1] = d_quotes
quotes[2] = my 'special' quote
*/
static int	remove_quotes_from_token(t_token	*token, int	*header)
{
	int	quotes[3];
	int	i;

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	quotes[2] = *header;
	while (token->content[i])
	{
		if (token->content[i] == 1)
		{
			quotes[2] = !quotes[2];
			delete_quotes_token(token, i);
			*header = quotes[2];
			if (!token->content)
				return (1);
		}
		else if (remove_quotes_content(token, quotes, &i) == 1)
		{
			*header = quotes[2];
			return (1);
		}
		*header = quotes[2];
	}
	return (0);
}

int	remove_quotes(t_list **list)
{
	t_list	*cur;
	t_token	*token;
	int		header;

	header = 0;
	cur = *list;
	while (cur)
	{
		token = cur->content;
		if (token->type != HERE_DOC)
		{
			if (remove_quotes_from_token(token, &header))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
