/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:33:45 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/27 15:23:22 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	expand_commands(t_list **parser, t_env *env)
{
	t_list	*cur;
	t_cmd	*cmd;

	cur = *parser;
	while (cur)
	{
		cmd = (t_cmd *)cur->content;
		search_and_expand(cmd, env);
		if (split_list(&cmd->word_list) || split_list(&cmd->token_list))
			return (1);
		remove_empties(&cmd->word_list);
		remove_empties(&cmd->token_list);
		if (remove_quotes(&cmd->word_list) || remove_quotes(&cmd->token_list))
			return (1);
		cur = cur->next;
	}
	return (0);
}
