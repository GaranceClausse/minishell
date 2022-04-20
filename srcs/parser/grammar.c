/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:42 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/20 16:02:24 by vkrajcov         ###   ########.fr       */
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

int	linebreak(t_lexer *lexer, int is_final)
{
	int	ret;
	t_token	*cur_token;

	ret = NOT_VALIDATED;
	cur_token = pick_token(lexer);
	if (!cur_token)
		return (ERROR);
	if (cur_token->type == NLINE)
	{
		ret = VALIDATED;
		if (!is_final)
		{
			feed_lexer(lexer, readline("pipe > "));
			linebreak(lexer, is_final);
		}
		else
		{
			cur_token = get_token(lexer);
			delete_token(cur_token);
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
	if (redir->type == REDIR_IN || redir->type == REDIR_OUT ||redir->type == HERE_DOC ||  redir->type == APPEND)
	{

		redir = get_token(lexer);
		word = pick_token(lexer);
		if (!word)
			return (ERROR);
		if (word->type == WORD)
		{
			word = get_token(lexer); //error?
			ft_swap_ptr((void **)&redir->content, (void **)&word->content);
			delete_token(word);
			if (add_token(&cmd->token_list, redir))
				return (ERROR);
			return (VALIDATED);
		}
		printf("Syntax Error");
		//print syntax error "parse error near <content>"
		return (SYNTAX_ERROR);
	}
	return (NOT_VALIDATED);
}

int	word_or_assign(t_lexer *lexer, t_cmd *cmd)
{
	t_token *cur;
	t_list	**list;

	cur = pick_token(lexer);
	if (!cur)
		return (ERROR);
	if (cur->type == ASSIGNMENT)
		list = &cmd->token_list;
	else if (cur->type == WORD)
		list = &cmd->word_list;
	if (cur->type == WORD || cur->type == ASSIGNMENT)
	{
		cur = get_token(lexer); //syntax error?
		//printf("cmd %p, list = %p, word = %p, token= %p\n", cmd, list, cmd->word_list, cmd->token_list);
		if (add_token(list, cur))
			return (ERROR);
		return (VALIDATED);
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

int	pipeline(t_lexer *lexer, t_list **parser)
{
	t_token *cur;
	int		ret;
	t_cmd	*cmd;

	cur = pick_token(lexer);
	if (!cur)
		return (ERROR);
	if (cur->type != PIPE)
		return (NOT_VALIDATED);
	delete_token(get_token(lexer));
	linebreak(lexer, 0);
	cmd = init_cmd();
	if (!cmd)
		return (ERROR);
	ret = command(lexer, cmd);
	if (ret == ERROR || ret == SYNTAX_ERROR)
		return (ERROR);
	if (ret == NOT_VALIDATED)
	{
		//print syntax error
		printf("Syntax Error");
		return (SYNTAX_ERROR);
	}
	if (add_cmd(parser, cmd))
		return (ERROR);
	if (linebreak(lexer, 1) == VALIDATED)
		return (VALIDATED);
	ret = pipeline(lexer, parser);
	if (ret == ERROR || ret == SYNTAX_ERROR)
		return (ret);
	return (VALIDATED); //make tests
}

int complete_command(t_lexer *lexer, t_list **parser)
{
	int	ret;
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (ERROR);

	ret = command(lexer, cmd);
	if (ret == ERROR || ret == SYNTAX_ERROR)
		return (ret);
	if (add_cmd(parser, cmd))
		return (ERROR);
	if (linebreak(lexer, 1) == VALIDATED)
	{
		cmd->is_in_pipe = 0;
		return (VALIDATED);
	}
	return (pipeline(lexer, parser));
}
