/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:04:13 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/04 16:09:22 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	expand_commands(t_env *env, t_list **parser)
{
	t_list	*cur;
	t_cmd	*cmd;
	cur = *parser;
	while (cur)
	{
		cmd = (t_cmd *)cur->content;
		search_and_expand(cmd, env);
		if (split_list(&cmd->wordlist) || split_list(&cmd->token_list))
			return (1);
		remove_empty_tokens(&cmd->wordlist);
		if (remove_quotes(&cmd->wordlist) || remove_quotes(&cmd->token_list))
			return (1);
		cur = cur->next;
	}
	remove_empty_cmds(parser);
	return (0);
}