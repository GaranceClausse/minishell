/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/21 17:30:44 by vkrajcov         ###   ########.fr       */
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

void	get_redir_type(t_token *token, char c)
{
	if (c == '>')
	{
		if (token->content[1])
			token->type = APPEND;
		else
			token->type = REDIR_OUT;
	}
	else if (c == '<')
	{
		if (token->content[1])
			token->type = HERE_DOC;
		else
			token->type = REDIR_IN;
	}
}

void	get_token_type(t_token *token, char c)
{
	int	i;
	int	eq;

	i = 1;
	eq = 0;
	if (c == '\n' || c == '\0')
	{
		token->type = NLINE;
		token->content = ft_strdup("newline");
	}
	else if (c == '|')
		token->type = PIPE;
	else if (c == '\"' || c == '\'' || is_special(c) == 0 || is_special(c) == 2)
	{
		while (token->content[i])
		{
			if (is_special(token->content[i]) == 2)
				eq++;
			i++;
		}
		if (eq != 0)
			token->type = ASSIGNMENT;
		else
			token->type = WORD;
	}
	else if (c == '<' || c == '>')
		get_redir_type(token, c);
}

int	fill_token(t_token *token, char c, int j, t_lexer *lexer)
{
	char	*str;

	if (c != '\0')
	{
		str = lexer->str + lexer->index;
		token->content = ft_substr(str, 0, j);
		if (!token->content)
			return (1);
		lexer->index += j;
	}
	get_token_type(token, c);
	return (0);
}

void	delete_token(void *token_void)
{
	t_token	*token;

	token = (t_token *)token_void;
	free(token->content);
	free(token);
}
