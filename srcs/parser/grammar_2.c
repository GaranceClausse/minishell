/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:38 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/21 17:30:42 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	syntax_error(char *err_msg, int is_freable)
{
	if (!err_msg)
		return (ERROR);
	write(2, err_msg, ft_strlen(err_msg));
	if (is_freable)
		free(err_msg);
	return (SYNTAX_ERROR);
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
	t_token	*cur;
	int		ret;
	t_cmd	*cmd;

	cur = pick_token(lexer);
	if (!cur)
		return (ERROR);
	if (cur->type == NOT_FINISHED)
		return (syntax_error("Syntax error: Unterminated quoted string\n", 0));
	if (cur->type != PIPE)
		return (NOT_VALIDATED);
	delete_token(get_token(lexer));
	linebreak(lexer, 0);
	cmd = init_cmd();
	if (!cmd)
		return (ERROR);
	ret = command(lexer, cmd);
	if (ret != VALIDATED)
	{	
		delete_cmd(cmd);
		if (ret == ERROR || ret == SYNTAX_ERROR)
			return (ret);
		cur = pick_token(lexer);
		return (syntax_error(ft_strjoin3("Syntax error near unexpected"
			"token \'", cur->content, "\'\n"), 1));
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

int	complete_command(t_lexer *lexer, t_list **parser)
{
	int		ret;
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (ERROR);
	ret = command(lexer, cmd);
	if (ret != VALIDATED)
	{
		delete_cmd(cmd);
		if (ret == NOT_VALIDATED && pick_token(lexer)->type != NLINE)
			return (syntax_error(ft_strjoin3("Syntax error near unexpected"
				"token \'", pick_token(lexer)->content, "\'\n"), 1));
		return (ret);
	}
	if (add_cmd(parser, cmd))
		return (ERROR);
	if (linebreak(lexer, 1) == VALIDATED)
	{
		cmd->is_in_pipe = 0;
		return (VALIDATED);
	}
	return (pipeline(lexer, parser));
}
