/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:39:48 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/08 22:20:34 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	add_token_next(t_list **token_list, t_type type, char *content)
{
	t_list	*new;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (1);
	token->type = type;
	token->content = content;
	new = ft_lstnew((void *)token);
	if (!new)
	{
		delete_token(token);
		return (1);
	}
	(*token_list)->next = new;
	return (0);
}

int	add_token_to_command(t_list **list, char **contents)
{
	t_list	*next;
	t_list	*cur;
	t_token	*token;
	int		i;

	cur = *list;
	next = cur->next;
	token = (t_token *)cur->content;
	i = 0;
	if (contents[i])
	{
		free(token->content);
		token->content = contents[i++];
	}
	while (contents[i])
	{
		if (add_token_next(&cur, token->type, contents[i]))
			break ;
		cur = cur->next;
		i++;
	}
	cur->next = next;
	return (i != 0 && contents[i] != 0);
}

int	split_list(t_list **list)
{
	t_list	*cur;
	t_token	*token;
	int		ret;
	char	**split_token;

	cur = *list;
	while (cur)
	{
		token = cur->content;
		split_token = iss_split(token->content, " \n\r\v\t\f");
		if (!split_token)
			return (1);
		ret = add_token_to_command(&cur, split_token);
		if (ret)
		{
			free_char_tab(split_token, ret);
			return (1);
		}
		cur = cur->next;
		free(split_token);
	}
	return (0);
}
