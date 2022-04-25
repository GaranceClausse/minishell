/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:23:20 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/25 11:37:22 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	extract_token(t_lexer *lexer)
{
	int		j;
	char	*str;

	str = lexer->str + lexer->index;
	while (*str == ' ')
	{
		str++;
		lexer->index++;
	}
	if (*str == '\n' || *str == '|' || *str == '\0')
		return (fill_token(lexer->token, *str, 1, lexer));
	else if (*str == '\"' || *str == '\'' || is_special(*str) == 0)
	{
		j = search_for_char(*str, str) + 1;
		if (is_special(*str) == 0)
			j = search_for_special(str);
		return (fill_token(lexer->token, *str, j, lexer));
	}
	else if (*str == '>' || *str == '<')
		return (fill_token(lexer->token, *str,
				1 + (*str + 1 && (*str == *(str + 1))), lexer));
	else if (*str == '=')
		return (fill_token(lexer->token, *str, search_for_special(str), lexer));
	return (0);
}

t_token	*pick_token(t_lexer	*lexer)
{
	if (!lexer->token)
	{
		lexer->token = malloc(sizeof(t_token));
		if (!lexer->token)
			return (NULL);
		lexer->token->type = NOT_FINISHED;
		lexer->token->content = NULL;
		if (extract_token(lexer))
		{
			free(lexer->token);
			lexer->token = NULL;
		}
	}
	return (lexer->token);
}

t_token	*get_token(t_lexer *lexer)
{
	t_token	*ret;

	ret = lexer->token;
	if (lexer->token)
		lexer->token = NULL;
	return (ret);
}
