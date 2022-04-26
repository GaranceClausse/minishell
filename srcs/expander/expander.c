/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:33:45 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/26 17:07:12 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int expand_commands(t_list **parser, t_env *env)
{
	t_list 	*cur;
	t_cmd	*cmd;

	cur = *parser;
	while (cur)
	{
		cmd = (t_cmd *)cur->content;
		if (expansion(cmd, env))
			return (1);
		if (split_list(&cmd->word_list) || split_list(&cmd->token_list))
			return (1);
		cur = cur->next;
	}
	return (0);
}