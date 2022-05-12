/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:33:50 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/12 20:22:16 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "libft.h"
#include "builtins.h"

static char	*get_directory_name(t_env *env, char **args)
{
	char	*directory;

	if (args[0])
	{
		if (args[1])
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			return (NULL);
		}
		return (ft_strdup(args[0]));
	}
	directory = get_value(env, "HOME");
	if (!directory || !ft_strcmp(directory, ""))
		ft_putstr_fd("cd: HOME not set\n", 2);
	return (directory);
}

static char	*join_pwd_to_path(char *pwd, char *curpath)
{
	char	*tmp;

	if (curpath[0] != '/' && pwd)
	{
		tmp = ft_strjoin3(pwd, "/", curpath);
		free(curpath);
		curpath = tmp;
		if (!curpath)
		{
			free(pwd);
			return (NULL);
		}
	}
	return (curpath);
}

static int	join_pwd(char *directory, char *pwd, char **curpath)
{
	int		show_absolute;
	char	*clean_path;

	show_absolute = (ft_strcmp(*curpath, directory) != 0);
	if (directory[0] != '/')
	{
		if (directory[0] != '.')
			free(directory);
		*curpath = join_pwd_to_path(pwd, *curpath);
		if (!*curpath)
		{
			free(pwd);
			return (1);
		}
		if (show_absolute)
		{
			clean_path = canonical_conversion(*curpath, directory);
			printf("%s\n", clean_path);
			free(clean_path);
		}
	}
	return (0);
}

static int	join_curpath(t_env *env, char *directory,
	char **curpath)
{
	if (directory[0] != '/' && directory[0] != '.')
	{
		*curpath = get_curpath_from_cdpath(env, directory);
		if (!*curpath)
		{
			free(directory);
			return (1);
		}
	}
	else
		*curpath = directory;
	return (0);
}

int	cd(t_env *env, char	**args)
{
	char	*directory;
	char	*curpath;
	char	*pwd;

	directory = get_directory_name(env, args);
	if (!directory)
		return (1);
	pwd = get_value(env, "PWD");
	if (join_curpath(env, directory, &curpath))
		return (1);
	if (join_pwd(directory, pwd, &curpath))
		return (1);
	directory = canonical_conversion(curpath, args[0]);
	free(curpath);
	if (!directory)
	{
		free(pwd);
		return (1);
	}
	curpath = directory;
	return (go_and_change_var(env, pwd, curpath, args[0]));
}
