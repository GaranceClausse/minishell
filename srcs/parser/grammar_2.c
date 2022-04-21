/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:38 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/21 11:34:18 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		printf("Syntax Error\n");
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

int	complete_command(t_lexer *lexer, t_list **parser)
{
	int		ret;
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
