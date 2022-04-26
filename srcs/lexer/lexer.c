/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/26 10:32:16 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	feed_lexer(t_lexer *lexer, char *str)
{
	if (lexer->str)
		free(lexer->str);
	if (lexer->token)
		delete_token(lexer->token);
	lexer->str = str;
	lexer->index = 0;
	lexer->token = NULL;
}

int	fill_token(t_token *token, char c, int j, t_lexer *lexer)
{
	char	*str;

	if (j != 0)
	{
		str = lexer->str + lexer->index;
		token->content = ft_substr(str, 0, j);
		if (!token->content)
			return (1);
		lexer->index += j;
		get_token_type(token, c);
	}
	return (0);
}

void	delete_token(void *token_void)
{
	t_token	*token;

	token = (t_token *)token_void;
	free(token->content);
	free(token);
}
