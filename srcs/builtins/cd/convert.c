/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:54:25 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/11 11:52:41 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	delete_from_char_tab(char **tab, int index)
{
	int	i;

	free(tab[index]);
	i = index;
	while (tab[i + 1])
	{
		tab[i] = tab[i + 1];
		i++;
	}
	tab[i] = tab[i + 1];
}

static int	dot_dot(int *i, char **canon_path, char *curpath, char **split)
{
	int	ret;

	if (!(*i))
	{
		free(*canon_path);
		*canon_path = ft_strdup("/");
		delete_from_char_tab(split, *i);
		return (0);
	}
	ret = check_folder_exists(*canon_path, curpath);
	if (ret != 1)
	{
		if (!ret)
			perror(curpath);
		free(*canon_path);
		free_char_tab(split, 0);
		return (1);
	}
	(*canon_path)[ft_strlen(*canon_path)
		- ft_strlen(split[(*i) - 1]) - 1] = '\0';
	delete_from_char_tab(split, *i);
	delete_from_char_tab(split, *i - 1);
	(*i)--;
	return (0);
}

static int	add_dir_curpath(char **canon_path, char **split, int *i)
{
	char	*tmp;

	tmp = ft_strjoin3(*canon_path, split[*i], "/");
	free(*canon_path);
	if (!tmp)
	{
		free_char_tab(split, 0);
		return (1);
	}
	*canon_path = tmp;
	(*i)++;
	return (0);
}

char	*canonical_conversion(char	*curpath)
{
	char	**split;
	char	*canon_path;
	int		i;

	split = ft_split(curpath, "/");
	if (!split)
		return (NULL);
	i = 0;
	canon_path = ft_strdup("/");
	while (split[i])
	{
		if (!ft_strcmp(split[i], ".."))
		{
			if (dot_dot(&i, &canon_path, curpath, split))
				return (NULL);
		}
		else if (!ft_strcmp(split[i], "."))
			delete_from_char_tab(split, i);
		else if (add_dir_curpath(&canon_path, split, &i))
			return (NULL);
	}
	free_char_tab(split, 0);
	if (ft_strlen(canon_path) > 1)
		canon_path[ft_strlen(canon_path) - 1] = '\0';
	return (canon_path);
}
