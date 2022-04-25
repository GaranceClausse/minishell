/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/25 11:40:07 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	feed_lexer(t_lexer *lexer, char *str)
{
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

static void	get_assign_or_word(t_token *token)
{
	int	i;
	int	is_simple;
	int	is_double;
	int	is_var;

	i = 1;
	is_simple = 0;
	is_double = 0;
	is_var = 0;

	if (token->content[0] == '=')
	{
		token->type = WORD;
		return;
	}
	while (token->content[i])
	{
		if (token->content[i] == '\'' && !is_double)
			is_simple = !is_simple;
		else if (token->content[i] == '\"' && !is_simple)
			is_double = !is_double;
		else if (token->content[i] == '$' && !is_double && !is_simple)
			is_var = 1;		
		else if (token->content[i] == '=' && !is_double && !is_simple && !is_var)
		{
			token->type = ASSIGNMENT;
			return;
		}
		i++;
	}
	token->type = WORD;
}

void	get_token_type(t_token *token, char c)
{
	if (c == '\n' || c == '\0')
		token->type = NLINE;
	else if (c == '|')
		token->type = PIPE;
	else if (c == '\"' || c == '\'' || is_special(c) == 0 || is_special(c) == 2)
		get_assign_or_word(token);
	else if (c == '<' || c == '>')
		get_redir_type(token, c);
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
