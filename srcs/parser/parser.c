/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:27:00 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/25 11:46:28 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//bash --posix

#include "parser.h"

int	add_cmd(t_list **parser, t_cmd *cmd)
{
	t_list	*new;
	void	*cmd_void;

	cmd_void = (void *)cmd;
	new = ft_lstnew(cmd_void);
	if (!new)
	{
		delete_cmd(cmd_void);
		return (1);
	}
	ft_lstadd_back(parser, new);
	return (0);
}

void	delete_parser(t_list **parser)
{
	ft_lstclear(parser, delete_cmd);
}

void	print_parser(t_list	**parser)
{
	t_list	*list;
	t_cmd	*cmd;

	list = *parser;
	while (list)
	{
		cmd = (t_cmd *)list->content;
		printf("words:\n");
		print_token(&cmd->word_list);
		printf("tokens:\n");
		print_token(&cmd->token_list);
		printf("\n\n\n");
		list = list->next;
	}
}
