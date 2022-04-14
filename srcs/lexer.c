/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/14 10:58:14 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	isinset(char c, char *str)
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

int	isspecial(char c)
{
	if (isinset(c, "|<>=$\n\t\v\r\f\"\'") || c == 32)
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
	while (isspecial(str[i]) == 0)
		i++;
	return (i);
}


t_token	get_token(char *str)
{
	int	i;
	int	j;
	t_token	token;

	i = 0;
	if (str[i] == '\"' || str[i] == '\'' || isspecial(str[i]) == 0)
	{

		j = search_for_char(str[i], str);
		if (isspecial(str[i]) == 0)
			j = search_for_special(str);
		if (j != -1)
		{
			token.content = ft_substr(str, 0, j);
			token.type = WORD;
		}

	}
	if (str[i + 1] && (str[i] == '>' || str[i] == '<'))
	{
		if (str[i] == str[i + 1])
			token.content = ft_substr(str, 0, 2);
		else
			token.content = ft_substr(str, 0 , 1);
		token.type = REDIRECTION;
	}
	if (str[i] == '\n' || str[i] == '|' || str[i] == '=')
		token.content = ft_substr(str, 0, 1);
	if (str[i] == '\n')
	       token.type = NEWLINE;
	if (str[i] == '|')
		token.type = PIPE;
	if (str[i] == '=')
		token.type = ASSIGNMENT;
	return (token);
}

int	main()
{
	t_token token;

	token = get_token("salut ca va?");
	printf("%s", token.content);
	printf("%u", token.type);
}
