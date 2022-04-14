/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:42:41 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/14 14:10:05 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_in_set(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_special(char c)
{
	if (is_in_set(c, " |<>=$\n\t\v\r\f\"\'"))
		return (1);
	return (0);
}

int	search_for_char(char c, char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{

		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	search_for_special(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_special(str[i]) == 0)
		i++;
	return (i);
}
