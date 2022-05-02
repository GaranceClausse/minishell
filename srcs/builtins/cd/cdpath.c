/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:35:18 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/02 11:42:53 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <error.h>
#include "env.h"

//	0 : Not found
//	-1 : Found but not accessible
//	1 : Found
int	check_folder_exists(char *curpath, char *directory)
{
	DIR		*dir;
	char	*prompt;

	dir = opendir(curpath);
	if (errno && errno != ENOENT)
	{
		prompt = ft_strjoin("cd: ", directory);
		if (!prompt)
			return (-1);
		perror(prompt);
		free(prompt);
		return (-1);
	}
	if (!errno)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

static char	*check_curpath_cdpath(char *curpath, char *directory)
{
	int	ret;

	if (!curpath)
		return (NULL);
	ret = check_folder_exists(curpath, directory);
	if (ret == 1)
	{
		ft_printf("%s\n", canonical_conversion(curpath));
		return (curpath);
	}
	free(curpath);
	if (ret == -1)
		return (NULL);
	return (ft_strdup(directory));
}

static char	*try_all_cdpaths(char **cdpath, char *directory)
{
	char	*curpath;

	while (*cdpath)
	{
		curpath = ft_strjoin3(*cdpath, "/", directory);
		curpath = check_curpath_cdpath(curpath, directory);
		if (!curpath || ft_strcmp(curpath, directory))
			return (curpath);
		cdpath++;
	}
	curpath = ft_strjoin("./", directory);
	return (check_curpath_cdpath(curpath, directory));
}

char	*get_curpath_from_cdpath(t_env *env, char *directory)
{
	char	**cdpath;
	char	*ret;

	ret = get_value(env, "CDPATH");
	if (!ret)
		return (NULL);
	if (ret[0] == '\0')
	{
		free(ret);
		return (ft_strdup(directory));
	}
	cdpath = ft_split(ret, ':');
	free(ret);
	if (!cdpath)
		return (NULL);
	ret = try_all_cdpaths(cdpath, directory);
	free_char_tab(cdpath, 0);
	return (ret);
}
