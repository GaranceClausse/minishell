/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/14 17:23:54 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	feed_lexer(t_lexer *lexer, char *str)
{
	lexer->str = str;
	lexer->index = 0;
	lexer->token.content = NULL;
}

t_token	get_token(t_lexer *lexer)
{
	int	i;
	int	j;
	t_token	token;
	char *str;

	i = 0;
	str = lexer->str + lexer->index;
	token.type = ERROR;
	token.content = NULL;
	if (str[i] == '\0')
	{
		token.content = NULL;
		token.type = NLINE;
		return (token);
	}
	if (str[i] == '\"' || str[i] == '\'' || is_special(str[i]) == 0)
	{
		j = search_for_char(str[i], str);
		if (is_special(str[i]) == 0)
			j = search_for_special(str);
		if (j != -1)
		{
			token.content = ft_substr(str, i, j);
			token.type = WORD;
			lexer->index += j;
		}

	}
	else if (str[i] == '>' || str[i] == '<')
	{
		if (str[i + 1] && (str[i] == str[i + 1]))
		{
			token.content = ft_substr(str, 0, 2);
			lexer->index += 2;
		}
		else
		{
			token.content = ft_substr(str, 0 , 1);
			lexer->index += 1;
		}
		token.type = REDIRECTION;
	}
	else if (str[i] == '\n' || str[i] == '|' || str[i] == '=')
	{
		token.content = ft_substr(str, 0, 1);
		lexer->index += 1;
	}
	if (str[i] == '\n' || str[i] == '\0')
	       token.type = NLINE;
	else if (str[i] == '|')
		token.type = PIPE;
	else if (str[i] == '=')
		token.type = ASSIGNMENT;
	return (token);
}

int	main()
{
	t_token token;
	t_lexer	lexer;
	char *str;

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
