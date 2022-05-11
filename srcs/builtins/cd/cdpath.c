/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:35:18 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/11 23:34:40 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <error.h>
#include "builtins.h"

//	0 : Not found
//	-1 : Found but not accessible
//	1 : Found
int	check_folder_exists(char *directory, char *cmd_name, int print)
{
	DIR		*dir;
	char	*prompt;

	errno = 0;
	dir = opendir(directory);
	if (errno && errno != ENOENT)
	{
		closedir(dir);
		if (print)
		{
			prompt = ft_strjoin("cd: ", cmd_name);
			if (!prompt)
				return (-1);
			ft_putstr_fd(prompt, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			free(prompt);
		}
		return (-1);
	}
	closedir(dir);
	return (!errno);
}

int	go_and_change_var(t_env *env, char *pwd,
	char *curpath, char *cmd_name)
{
	int		ret;
	char	*prompt;

	ret = chdir(curpath);
	if (ret)
	{
		prompt = ft_strjoin("cd: ", cmd_name);
		perror(prompt);
		free(prompt);
		free(pwd);
		free(curpath);
		return (1);
	}
	ret = change_var_by_val(env, &env->env_var, "OLDPWD", pwd);
	free(pwd);
	if (ret)
	{
		free(curpath);
		return (1);
	}
	ret = change_var_by_val(env, &env->env_var, "PWD", curpath);
	free(curpath);
	return (ret);
}

static char	*check_curpath_cdpath(char *curpath, char *directory)
{
	int		ret;

	if (!curpath)
		return (NULL);
	ret = check_folder_exists(curpath, directory, 0);
	if (ret == 1)
		return (curpath);
	free(curpath);
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
	cdpath = ft_split(ret, ":");
	free(ret);
	if (!cdpath)
		return (NULL);
	ret = try_all_cdpaths(cdpath, directory);
	free_char_tab(cdpath, 0);
	return (ret);
}
