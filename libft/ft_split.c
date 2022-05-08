/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:48:45 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/08 22:48:32 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_words(const char *s, char *c)
{
	int		cpt;

	if (!s)
		return (0);
	cpt = 0;
	while (*s)
	{
		if (*s == *c)
		{
			cpt++;
			while (*s == *c)
				s++;
		}
		else
			s++;
	}
	return (cpt + 1);
}

static void	free_tab(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

static int	add_word(char **tab, int i, char *word)
{
	tab[i] = word;
	if (!word)
	{
		free_tab(tab);
		return (0);
	}
	return (1);
}

static char	**spliter(char **split, const char *s, char c, size_t len)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	end = 0;
	len = ft_strlen(s);
	while (end <= len)
	{
		if (end == len || s[end] == c)
		{
			if (end != start
				&& !add_word(split, i++, ft_substr(s, start, end - start)))
			{
				return (NULL);
			}
			while (s[end] && s[end] == c)
				end++;
			start = end;
		}
		end++;
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *str, char *c)
{
	char	**split;
	char	*s;

	s = ft_strtrim(str, c);
	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
	{
		free(s);
		return (NULL);
	}
	spliter(split, str, *c, ft_strlen(str));
	free(s);
	return (split);
}
