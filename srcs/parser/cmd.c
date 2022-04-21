/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:46 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/20 16:07:37 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->word_list = NULL;
	cmd->token_list = NULL;
	cmd->is_in_pipe = 1;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	return (cmd);
}

void	delete_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = (void *)cmd_void;

	if (cmd->word_list)
		ft_lstclear(&cmd->word_list, delete_token);
	if (cmd->token_list)
		ft_lstclear(&cmd->token_list, delete_token);
	free(cmd);
}

void	print_token(t_list	**token_list)
{
	t_token	*cur_token;
	t_list	*cur;
	cur = *token_list;
	while (cur)
	{
		cur_token = (t_token *)cur->content;
		printf("type = %d val = %s\n", cur_token->type, cur_token->content);
		cur = cur->next;
	}
}
int	add_token(t_list **token_list, t_token *token)
{
	t_list *new;

	new = ft_lstnew((void *)token);
	if (!new)
		return (1);
	ft_lstadd_back(token_list, new);
	return (0);
}
