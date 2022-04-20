/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:51:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2021/12/02 09:45:53 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*cur;

	if (alst)
	{
		cur = *alst;
		if (cur == NULL)
			*alst = new;
		else
		{
			cur = ft_lstlast(cur);
			cur->next = new;
		}
	}
}