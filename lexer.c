/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:22 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/13 17:56:45 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int	ft_strlen(const char *str)
{
	int	i = 0;
	while(str[i])
		i++;
	return i;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*cpy;

	i = 0;
	if (!s)
		return (NULL);
	if (len <= ft_strlen(s))
		cpy = malloc(sizeof(char) * (len + 1));
	else
		cpy = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!cpy)
		return (NULL);
	if (start > ft_strlen(s))
	{
		cpy[0] = '\0';
		return (cpy);
	}
	while (s[start] && i < len)
	{
		cpy[i] = s[start];
		i++;
		start++;
	}
	cpy[i] = '\0';
	return (cpy);
}

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
	if (isinset(c, "|<>=$\n\t\v\r\f\"\'"))
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
	return (token);
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	t_token token;

	i = 1;
	if (argc > 0)
	{
		while (argv[i])
		{
			token = get_token(argv[i]);
			printf("%s\n", token.content);
			i++;
		
		}
	}

}
