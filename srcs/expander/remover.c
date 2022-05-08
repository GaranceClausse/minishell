/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:56:43 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/08 19:14:06 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

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
