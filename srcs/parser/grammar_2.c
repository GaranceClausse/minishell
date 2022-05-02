/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:38 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/02 17:38:35 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	command(t_lexer *lexer, t_cmd *cmd)
{
	int		ret;

	ret = prefix_suffix(lexer, cmd, 1);
	if (ret == NOT_VALIDATED)
		ret = prefix_suffix(lexer, cmd, 0);
	if (ret == VALIDATED)
	{
		ret = command(lexer, cmd);
		if (ret == VALIDATED || ret == NOT_VALIDATED)
			return (VALIDATED);
	}
	return (ret);
}

static int	destroy_cmd_and_exit(t_cmd *cmd, int ret, t_token *cur)
{
	delete_cmd(cmd);
	if (!cur)
		return (ERROR);
	if (ret == NOT_VALIDATED && cur->type != NLINE) //check NLINE
	{
		return (syntax_error(ft_strjoin3("Syntax error near unexpected"
					" token \'", cur->content, "\'\n"), 1));
	}
	return (ret);
}

static int	pipeline(t_lexer *lexer, t_list **parser)
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
	ret = linebreak(lexer, 0);
	if (ret == ERROR || ret == SYNTAX_ERROR)
		return (ret);
	cmd = init_cmd();
	if (!cmd)
		return (ERROR);
	ret = command(lexer, cmd);
	if (ret != VALIDATED)
		return (destroy_cmd_and_exit(cmd, ret, pick_token(lexer)));
	if (add_cmd(parser, cmd))
		return (ERROR);
	ret = linebreak(lexer, 1);
	if (ret != NOT_VALIDATED)
		return (ret);
	ret = pipeline(lexer, parser);
	if (ret == ERROR || ret == SYNTAX_ERROR)
		return (ret);
	return (VALIDATED);
}

int	complete_command(t_lexer *lexer, t_list **parser)
{
	int		ret;
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (ERROR);
	ret = command(lexer, cmd);
	if (ret == VALIDATED)
	{
		if (add_cmd(parser, cmd))
			return (ERROR);
		ret = linebreak(lexer, 1);
		if (ret == VALIDATED)
		{
			cmd->is_in_pipe = 0;
			return (VALIDATED);
		}
		if (ret != NOT_VALIDATED)
			return (ret);
		return (pipeline(lexer, parser));
	}
	return (destroy_cmd_and_exit(cmd, ret, pick_token(lexer)));
}
