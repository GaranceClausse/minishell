/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:06:50 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/26 15:06:57 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char *set)
{
	int		cpt;
	int		is_d_quote;
	int		is_s_quote;

	is_d_quote = 0;
	is_s_quote = 0;
	cpt = 0;
	while (*s)
	{
		if (*s == '\'' && !is_d_quote)
			is_s_quote = !is_s_quote;
		else if (*s == '"' && !is_s_quote)
			is_d_quote = !is_d_quote;
		else if (ft_is_in_set(*s, set) && !is_d_quote && !is_s_quote)
		{
			cpt++;
			while (ft_is_in_set(*(++s), set));
			s--;
		}
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

static char	**spliter(char **split, const char *s, char *iss)
{
	int	i;
	int	count_word;
	int	is_d_quote;
	int	is_s_quote;

	i = 0;
	count_word = 0;
	is_d_quote = 0;
	is_s_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !is_d_quote)
			is_s_quote = !is_s_quote;
		else if (s[i] == '"' && !is_s_quote)
			is_d_quote = !is_d_quote;
		else if (ft_is_in_set(s[i], iss) && !is_d_quote && !is_s_quote)
		{
			if (!add_word(split, count_word++, ft_substr(s, 0, i)))
				return (NULL);
			while (ft_is_in_set(s[++i], iss));
			s += i;
			i = -1;
		}
		i++;
	}
	if (i && !add_word(split, count_word++, ft_substr(s, 0, i)))
		return (NULL);
	split[count_word] = NULL;
	return (split);
}

char	**ft_split(const char *str, char *iss)
{
	char	**split;
	char	*tmp;

	tmp = ft_strtrim(str, iss);
	if (!tmp)
		return (NULL);
	split = malloc(sizeof(char *) * (count_words(tmp, iss) + 1));
	if (!split)
	{
		free(tmp);
		return(NULL);
	}
	spliter(split, tmp, iss);
	free(tmp);
	return (split);
}