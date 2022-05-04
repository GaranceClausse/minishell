/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:42 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/04 14:16:33 by gclausse         ###   ########.fr       */
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
// cmmand           : io_redirect 	  cmd_cpl
//                  | ASSIGNMENT_WORD cmd_cpl
//                  | WORD		      cmd_cpl
//					| io_redirect
//                  | ASSIGNMENT_WORD
//                  | WORD
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
