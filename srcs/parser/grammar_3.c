/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:01:52 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/04 14:16:36 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_word_redirect(t_lexer *lexer, t_cmd *cmd, t_token *redir)
{
	t_token	*word;

	word = pick_token(lexer);
	if (!word || word->type == NOT_FINISHED || word->type != WORD)
	{
		delete_token(redir);
		if (!word)
			return (ERROR);
		if (word->type == NOT_FINISHED)
			return (syntax_error("Syntax error:"
					"Unterminated quoted string\n", 0));
		return (syntax_error(ft_strjoin3("Syntax error near "
					"unexpected token \'", word->content, "\'\n"), 1));
	}
	word = get_token(lexer);
	ft_swap_ptr((void **)&redir->content, (void **)&word->content);
	delete_token(word);
	if (add_token(&cmd->token_list, redir))
		return (ERROR);
	return (VALIDATED);
}

static int	io_redirect(t_lexer *lexer, t_cmd *cmd)
{
	t_token	*redir;

	redir = pick_token(lexer);
	if (!redir)
		return (ERROR);
	if (redir->type == NOT_FINISHED)
		return (syntax_error("Syntax error: Unterminated quoted string\n", 0));
	if (redir->type < REDIR_IN || redir->type > APPEND)
		return (NOT_VALIDATED);
	redir = get_token(lexer);
	return (get_word_redirect(lexer, cmd, redir));
}

static int	word_or_assign(t_lexer *lexer, t_cmd *cmd, int is_prefix)
{
	t_token	*cur;
	t_list	**list;

	cur = pick_token(lexer);
	if (!cur)
		return (ERROR);
	if (cur->type == NOT_FINISHED)
		return (syntax_error("Syntax error: Unterminated quoted string\n", 0));
	if ((cur->type != WORD && cur->type != ASSIGNMENT)
		|| (cur->type == WORD && is_prefix))
		return (NOT_VALIDATED);
	if (is_prefix == 0)
		cur->type = WORD;
	if (cur->type == ASSIGNMENT)
		list = &cmd->token_list;
	else
		list = &cmd->wordlist;
	cur = get_token(lexer);
	if (add_token(list, cur))
		return (ERROR);
	return (VALIDATED);
}

int	prefix_suffix(t_lexer *lexer, t_cmd *cmd, int is_prefix)
{
	int		ret;

	ret = io_redirect(lexer, cmd);
	if (ret == NOT_VALIDATED)
		ret = word_or_assign(lexer, cmd, is_prefix);
	if (ret == VALIDATED)
	{
		ret = prefix_suffix(lexer, cmd, is_prefix);
		if (ret == VALIDATED || ret == NOT_VALIDATED)
			return (VALIDATED);
	}
	return (ret);
}
