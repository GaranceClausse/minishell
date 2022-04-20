/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:42 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/20 12:26:44 by vkrajcov         ###   ########.fr       */
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
// cmd_cpl          : io_redirect 	  cmd_cpl
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

int	linebreak(t_lexer *lexer)
{
	int	ret;
	t_token	*cur_token;

	ret = NOT_VALIDATED;
	// verifier si ca return NULL
	while (pick_token(lexer)->type == NLINE)
	{
		cur_token = get_token(lexer);
		delete_token(cur_token);
		ret = VALIDATED;
	}
	return (ret);
}

int	io_redirect(t_lexer *lexer, t_cmd *cmd)
{
	t_token	*redir;
	t_token	*word;

	redir = pick_token(lexer);
	if (redir->type == REDIR_IN || redir->type == REDIR_OUT ||redir->type == HERE_DOC ||  redir->type == APPEND)
	{
		redir = get_token(lexer);
		if (pick_token(lexer)->type == WORD)
		{
			word = get_token(lexer); //error?
			ft_swap(&redir->content, &word->content);
			delete_token(word);
			if(!add_token(&cmd->token_list, redir))
				return (ERROR);
			return (VALIDATED);
		}
		//print syntax error "parse error near <content>"
		return (SYNTAX_ERROR);
	}
	return (NOT_VALIDATED);
}

int	word_or_assign(t_lexer *lexer, t_cmd *cmd)
{
	t_token *cur;
	t_list	*list;

	cur = pick_token(lexer)->type;
	if (cur == ASSIGNMENT)
		list = cmd->token_list;
	else if (cur == WORD)
		list = cmd->word_list;
	if (cur == WORD || cur == ASSIGNMENT)
	{
		cur = get_token(lexer); //syntax error?
		if(!add_token(&list, cur))
			return (ERROR);
		return (VALIDATED)
	}
	return (NOT_VALIDATED);
}

int	command(t_lexer *lexer, t_cmd *cmd)
{
	int		ret;

	ret = io_redirect(lexer, cmd);
	if (ret == SYNTAX_ERROR || ret == ERROR)
		return (ret);
	if (ret != VALIDATED)
		ret = word_or_assign(lexer, cmd);
	if (ret == VALIDATED)
	{
		ret = command(lexer, cmd); 
		if (ret == SYNTAX_ERROR || ret == ERROR)
			return (ret);
		return (VALIDATED);
	}
	return (NOT_VALIDATED);
}

int	pipeline(t_lexer *lexer, t_cmd *cmd)
{
	t_token *cur;
	int		ret;

	if (pick_token(lexer)->type != PIPE)
		return (NOT_VALIDATED);
	delete_token(get_token(lexer));
	linebreak(lexer);
	ret = command(lexer, cmd);
	if (ret == ERROR || ret == SYNTAX_ERROR)
		return (ERROR);
	if (ret == NOT_VALIDATED)
	{
		//print syntax error
		return (SYNTAX_ERROR);
	}
	if (linebreak(lexer) == VALIDATED)
		return (VALIDATED)
	ret = pipeline(lexer, cmd);
	if (ret == ERROR || ret == SYNTAX_ERROR)
		return (ret);
	return (VALIDATED); //make tests
}

int complete_command(t_lexer *lexer, t_cmd *cmd)
{
	int	ret;

	ret = command(lexer, command);
	if (ret == ERROR || ret == SYNTAX_ERROR)
		return (ret);
	if (linebreak(lexer) == VALIDATED)
	{
		cmd->is_in_pipe = 0;
		return (VALIDATED);
	}
	return (pipeline(lexer, cmd));
}
