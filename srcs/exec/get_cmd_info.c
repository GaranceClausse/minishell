/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:28:09 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 11:56:41 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_list_len(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	**token_to_wordlist(t_list *token_list)
{
	t_token	*cur;
	char	**word_list;
	int		i;

	i= 0;
	word_list = malloc(sizeof(char *) * (get_list_len(token_list) + 1));
	if (!word_list)
		return (NULL);
	while (token_list)
	{
		cur = (t_token *)token_list->content;
		word_list[i] = cur->content;
		token_list = token_list->next;
		i++;
	}
	word_list[i] = NULL;
	return (word_list);
}
