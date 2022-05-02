/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:35:18 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/02 11:58:55 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <error.h>
#include "builtins.h"

//	0 : Not found
//	-1 : Found but not accessible
//	1 : Found
int	check_folder_exists(char *curpath, char *directory)
{
	DIR		*dir;
	char	*prompt;

	dir = opendir(curpath);
	closedir(dir);
	if (errno && errno != ENOENT)
	{
		prompt = ft_strjoin("cd: ", directory);
		if (!prompt)
			return (-1);
		perror(prompt);
		free(prompt);
		return (-1);
	}
	return (!errno);
}

static char	*check_curpath_cdpath(char *curpath, char *directory)
{
	int		ret;
	char	*clean_path;

	if (!curpath)
		return (NULL);
	ret = check_folder_exists(curpath, directory);
	if (ret == 1)
	{
		clean_path = canonical_conversion(curpath);
		ft_printf("%s\n", clean_path);
		free(clean_path);
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
		free(curpath);
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
