/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iss_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:20:03 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/08 22:32:47 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_split
{
	char	**split;
	int		count_word;
	int		is_s_quote;
	int		is_d_quote;
}	t_split;

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
			while (ft_is_in_set(*s, set))
				s++;
			s--;
		}
		s++;
	}
	return (cpt + 1);
}

static int	add_word(char **tab, int i, char *word)
{
	tab[i] = word;
	if (!word)
	{
		free_char_tab(tab, 0);
		return (0);
	}
	return (1);
}

static int	check_s_and_add(t_split *data, char **s, char *iss, int *i)
{
	if ((*s)[*i] == '\'' && !data->is_d_quote)
		data->is_s_quote = data->is_s_quote;
	else if ((*s)[*i] == '"' && !data->is_s_quote)
		data->is_d_quote = !data->is_d_quote;
	else if (ft_is_in_set((*s)[*i], iss) && !data->is_d_quote && !data->is_s_quote)
	{
		if (!add_word(data->split, data->count_word++, ft_substr(*s, 0, *i)))
			return (1);
		while (ft_is_in_set((*s)[*i], iss))
			(*i)++;
		*s += (*i);
		*i = -1;
	}
	return (0);
}

static char	**spliter(char **split, char *s, char *iss)
{
	int		i;
	t_split	data;

	i = 0;
	data.split = split;
	data.count_word = 0;
	data.is_s_quote = 0;
	data.is_d_quote = 0;
	while (s[i])
	{
		if (check_s_and_add(&data, &s, iss, &i))
			return (NULL);
		i++;
	}
	if (i && !add_word(split, data.count_word++, ft_substr(s, 0, i)))
		return (NULL);
	split[data.count_word] = NULL;
	return (split);
}

char	**iss_split(const char *str, char *iss)
{
	char	*tmp;
	char	**split;

	tmp = ft_strtrim(str, iss);
	if (!tmp)
		return (NULL);
	split = malloc(sizeof(char *) * (count_words(tmp, iss) + 1));
	if (!split)
	{
		free(tmp);
		return (NULL);
	}
	spliter(split, tmp, iss);
	free(tmp);
	return (split);
}
