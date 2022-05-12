/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/12 13:31:50 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*init_lexer(void)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->str = NULL;
	lexer->token = NULL;
	feed_lexer(lexer, NULL);
	return (lexer);
}

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
