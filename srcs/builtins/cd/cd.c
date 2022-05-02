/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:33:50 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/02 11:59:24 by vkrajcov         ###   ########.fr       */
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
			write (2, "cd : too many arguments\n", 24);
			return (NULL);
		}
		return (ft_strdup(args[0]));
	}
	directory = get_value(env, "HOME");
	if (!directory)
		write(2, "cd : HOME not set\n", 18);
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

static int	go_and_change_var(t_env *env, char *pwd, char *curpath)
{
	int	ret;

	ret = chdir(curpath);
	if (ret)
	{
		perror("cd");
		free(pwd);
		free(curpath);
		return (ret);
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

int	cd(t_env *env, char	**args)
{
	char	*directory;
	char	*curpath;
	char	*pwd;

	directory = get_directory_name(env, args);
	if (!directory)
		return (1);
	curpath = directory;
	if (directory[0] != '/' && directory[0] != '.')
	{
		curpath = get_curpath_from_cdpath(env, directory);
		free(directory);
		if (!curpath)
			return (1);
	}
	pwd = get_value(env, "PWD");
	curpath = join_pwd_to_path(pwd, curpath);
	if (!curpath)
		return (1);
	directory = canonical_conversion(curpath);
	free(curpath);
	if (!directory)
		return (1);
	curpath = directory;
	return (go_and_change_var(env, pwd, curpath));
}
