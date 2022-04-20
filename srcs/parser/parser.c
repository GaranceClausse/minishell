/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:27:00 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/20 12:27:10 by vkrajcov         ###   ########.fr       */
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

int main()
{
	t_list	*parser;

	parser = NULL;
	add_cmd(&parser, feed_cmd(NULL));
	add_cmd(&parser, feed_cmd(NULL));
	delete_parser(&parser);
	
	return (0);
}