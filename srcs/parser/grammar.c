/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:42 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/02 15:15:37 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//%start  complete_command
//%%
// complete_command : command linebreak
//                  | command pipeline
//                  ; 
// pipeline		    : '|' linebreak command linebreak
//					| '|' command linebreak
//					| '|' linebreak command pipeline
//					| '|' command pipeline
//                  ;
// command          : prefix WORD suffix
//                  | prefix WORD
//                  | prefix
//					| WORD
//                  | WORD suffix
//                  | suffix
//					;
// suffix			: io_redirect suffix
//					| WORD	      suffix
//					| io_redirect
//					| WORD
//					;
// prefix           : io_redirect prefix
//					| ASSIGNMENT_WORD prefix
//					| ASSIGNMENT_WORD
//					| io_redirect
//					;
// io_redirect      : '<'       WORD
//                  | '>'       WORD
//                  | DGREAT    WORD
// 			        | DLESS     WORD 
//                  ;
// linebreak		: 			   NEWLINE
//					: newline_list NEWLINE
//         

#include "parser.h"

int	g_last_return = 0;

int	multiline(t_lexer *lexer, char *delimiter)
{
	char	*usr_input;
	void	*old_getc;
	int		tmp;

	(void)delimiter;
	tmp = g_last_return;
	g_last_return = 0;
	signal(SIGINT, sigint_handler);
	old_getc = rl_getc_function;
	rl_getc_function = getc;
	write(1, "pipe > ", 8);
	usr_input = readline(NULL);
	while (!usr_input && g_last_return != 130)
		usr_input = readline(NULL);
	rl_getc_function = old_getc;
	if (g_last_return)
		return (1);
	feed_lexer(lexer, usr_input);
	g_last_return = tmp;
	return (0);
}

int	linebreak(t_lexer *lexer, int is_final)
{
	int		ret;
	t_token	*cur_token;

	ret = NOT_VALIDATED;
	cur_token = pick_token(lexer);
	if (!cur_token)
		return (ERROR);
	if (cur_token->type == NOT_FINISHED)
		return (syntax_error("Syntax error: Unterminated quoted string\n", 0));
	if (cur_token->type == NLINE)
	{
		ret = VALIDATED;
		delete_token(get_token(lexer));
		if (!is_final)
		{
			if (multiline(lexer, NULL))
				return (ERROR);
			ret = linebreak(lexer, is_final);
			if (ret == ERROR || ret == SYNTAX_ERROR)
				return (ret);
		}
	}
	return (ret);
}

int	io_redirect(t_lexer *lexer, t_cmd *cmd)
{
	t_token	*redir;
	t_token	*word;

	redir = pick_token(lexer);
	if (!redir)
		return (ERROR);
	if (redir->type == NOT_FINISHED)
		return (syntax_error("Syntax error: Unterminated quoted string\n", 0));
	if (redir->type < REDIR_IN || redir->type > APPEND)
		return (NOT_VALIDATED);
	redir = get_token(lexer);
	word = pick_token(lexer);
	if (!word)
	{
		delete_token(redir);
		return (ERROR);
	}
	if (word->type == NOT_FINISHED)
	{
		delete_token(redir);
		return (syntax_error("Syntax error: Unterminated quoted string\n", 0));
	}
	if (word->type == WORD)
	{
		word = get_token(lexer);
		ft_swap_ptr((void **)&redir->content, (void **)&word->content);
		delete_token(word);
		if (add_token(&cmd->token_list, redir))
			return (ERROR);
		return (VALIDATED);
	}
	delete_token(redir);
	return (syntax_error(ft_strjoin3("Syntax error near "
				"unexpected token \'", word->content, "\'\n"), 1));
}

int	word_or_assign(t_lexer *lexer, t_cmd *cmd)
{
	t_token	*cur;
	t_list	**list;

	cur = pick_token(lexer);
	if (!cur)
		return (ERROR);
	if (cur->type == NOT_FINISHED)
		return (syntax_error("Syntax error: Unterminated quoted string\n", 0));
	if (cur->type == ASSIGNMENT)
		list = &cmd->token_list;
	else if (cur->type == WORD)
		list = &cmd->word_list;
	if (cur->type == WORD || cur->type == ASSIGNMENT)
	{
		cur = get_token(lexer);
		if (add_token(list, cur))
			return (ERROR);
		return (VALIDATED);
	}
	return (NOT_VALIDATED);
}
