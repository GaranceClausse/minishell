/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:34:26 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/11 15:16:37 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

	i = 1;
	is_simple = 0;
	is_double = 0;
	token->type = WORD;
	if (token->content[0] == '=')
		return ;
	while (token->content[i])
	{
		if (token->content[i] == '\'' && !is_double)
			is_simple = !is_simple;
		else if (token->content[i] == '\"' && !is_simple)
			is_double = !is_double;
		else if (token->content[i] == '=')
		{
			token->type = ASSIGNMENT;
			return ;
		}
		i++;
	}
	return ;
}

void	get_token_type(t_token *token, char c)
{
	if (c == '\n' || c == '\0')
	{
		token->type = NLINE;
		free(token->content);
		token->content = ft_strdup("newline");
	}
	else if (c == '|')
		token->type = PIPE;
	else if (c == '\"' || c == '\'' || is_special(c) == 0 || is_special(c) == 2)
		get_assign_or_word(token);
	else if (c == '<' || c == '>')
		get_redir_type(token, c);
}
