/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:38 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/03 17:36:46 by vkrajcov         ###   ########.fr       */
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
	int	ret_prefix;
	int	ret_suffix;

	ret_prefix = (prefix_suffix(lexer, cmd, 1));
	if (ret_prefix == ERROR || ret_prefix == SYNTAX_ERROR)
		return (ret_prefix);
	ret_suffix = (prefix_suffix(lexer, cmd, 0));
	if (ret_suffix == ERROR || ret_suffix == SYNTAX_ERROR)
		return (ret_suffix);
	if (ret_prefix == VALIDATED || ret_suffix == VALIDATED)
		return (VALIDATED);
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
		return (SYNTAX_ERROR);
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
	ret = linebreak(lexer, 1);
	if (ret == ERROR || ret == SYNTAX_ERROR)
		return (ret);
	if (ret == VALIDATED)
	{
		cmd->is_in_pipe = 0;
		return (ret);
	}
	return (pipeline(lexer, parser));
}
