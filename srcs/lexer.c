/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/20 14:47:09 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	feed_lexer(t_lexer *lexer, char *str)
{
	lexer->str = str;
	lexer->index = 0;
	lexer->token = NULL;
}

void	get_token_type(t_token *token, char c)
{
	int	i;
	int	eq;

	i = 1;
	eq = 0;
	if (c == '\n' || c == '\0')
		token->type = NLINE;
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
	else if (c == '>')
	{
		if (token->content[i])
			token->type = APPEND;
		else
			token->type = REDIR_OUT;
	}
	else if (c == '<')
	{
		if (token->content[i])
			token->type = HERE_DOC;
		else
			token->type = REDIR_IN;
	}
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
		if (j != 0)
			return (fill_token(lexer->token, *str, j, lexer));
	}
	else if (*str == '>' || *str == '<')
		return (fill_token(lexer->token, *str,
			1 + (*str + 1 && (*str == *(str + 1))), lexer));
	else if (*str == '=' && (*str + 1 && is_special(*(str + 1)) == 0))
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
		lexer->token->type = UNINITIALIZED;
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

void	delete_token(void *token_void)
{
	t_token	*token;

	token = (t_token *)token_void;
	free(token->content);
	free(token);
}