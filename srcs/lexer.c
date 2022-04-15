/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/15 15:57:19 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	feed_lexer(t_lexer *lexer, char *str)
{
	lexer->str = str;
	lexer->index = 0;
	lexer->token.content = NULL;
}

void	get_token_type(t_token *token, char c)
{
	if (c == '\n' || c == '\0')
		token->type = NLINE;
	else if (c == '|')
		token->type = PIPE;
	else if (c == '=')
		token->type = ASSIGNMENT;
	else if (c == '\"' || c == '\'' || is_special(c) == 0)
		token->type = WORD;
	else if (c == '>' || c == '<')
		token->type = REDIRECTION;
}

void	fill_token(t_token *token, char c, int j, t_lexer *lexer)
{
	char	*str;

	if (c != '\0')
	{
		str = lexer->str + lexer->index;
		token->content = ft_substr(str, 0, j);
		lexer->index += j;
	}
	get_token_type(token, c);
}

t_token	get_token(t_lexer *lexer)
{
	int		j;
	t_token	token;
	char	*str;

	str = lexer->str + lexer->index;
	token.type = ERROR;
	token.content = NULL;
	if (*str == '\n' || *str == '|' || *str == '=' || *str == '\0')
		fill_token(&token, *str, 1, lexer);
	else if (*str == '\"' || *str == '\'' || is_special(*str) == 0)
	{
		j = search_for_char(*str, str) + 1;
		if (is_special(*str) == 0)
			j = search_for_special(str);
		if (j != 0)
			fill_token(&token, *str, j, lexer);
	}
	else if (*str == '>' || *str == '<')
		fill_token(&token, *str,
			1 + (*str + 1 && (*str == *(str + 1))), lexer);
	return (token);
}

int	main(void)
{
	t_token	token;
	t_lexer	lexer;
	char	*str;

	str = readline(NULL);
	while (str) // readline up to EOF
	{
		feed_lexer(&lexer, str); //lexer as paramater
		//parser check if executable if not then
		token = get_token(&lexer);
		printf("token.content = %s\n", token.content);
		printf("token.type = %u\n\n", token.type);
		while (token.content != NULL) //parser is not error and not finished
		{
			if (lexer.str[lexer.index] == ' ')
				lexer.index += 1;
			token = get_token(&lexer); //parser is asking for new token
			printf("token.content = %s\n", token.content);
			printf("token.type = %u\n\n", token.type);
		}
	str = readline(NULL);
	}
}
