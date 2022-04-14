/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/14 15:06:50 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	feed_lexer(char *str)
{
	t_lexer	lexer;
	int i = 0;

	lexer.index = 0;
	lexer.str = str;
	while (str[lexer.index])
	{
		if (str[lexer.index] == ' ')
			lexer.index += 1;
		lexer.token = get_token(&lexer);
		printf("index = %d\n", lexer.index);
		printf("content = %s\n", lexer.token.content);
		printf("type = %u\n", lexer.token.type);
		printf("new str = %s\n\n", &str[lexer.index]);

		i++;
	}

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
		token.type = ENDOF;
		token.content = NULL;
		return (token);
	}
	else if (str[i] == '\"' || str[i] == '\'' || is_special(str[i]) == 0)
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
	else if (str[i + 1] && (str[i] == '>' || str[i] == '<'))
	{
		if (str[i] == str[i + 1])
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
	else if (str[i] == '\n')
	       token.type = NEWLINE;
	else if (str[i] == '|')
		token.type = PIPE;
	else if (str[i] == '=')
		token.type = ASSIGNMENT;
	return (token);
}

int	main()
{
	feed_lexer("salut ca< v >?");
}
