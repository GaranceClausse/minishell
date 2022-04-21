/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:42:41 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/21 14:09:28 by gclausse         ###   ########.fr       */
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
		if (c == '=')
			return (2);
		i++;
	}
	return (0);
}

int	is_special(char c)
{
	if (is_in_set(c, " |<>$\n\t\v\r\f") == 1)
		return (1);
	else if (is_in_set(c, " |<>$\n\t\v\r\f") == 2)
		return (2);
	return (0);
}

int	search_for_char(char c, char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (-1);
}

int	search_for_special(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (is_special(str[i]) == 0 || is_special(str[i]) == 2))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (search_for_char(str[i], &str[i]) == -1)
				return (0);
			i += search_for_char(str[i], &str[i]);
		}
		i++;
	}
	return (i);
}
