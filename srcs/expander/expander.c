/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:04:13 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/10 16:49:46 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
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
		redir(env, cmd);
		cur = cur->next;
	}
	return (0);
}
