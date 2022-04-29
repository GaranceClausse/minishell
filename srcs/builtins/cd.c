/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:33:50 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/28 17:55:11 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys.types.h>
#include <dirent.h>
#include <error.h>
#include <unistd.h>
#include "env.h"
#include "libft.h"
//cd uniquement avec un chemin relatif ou absolu
//getcw -> relatif 
//get current working directory as absolute path
// chdir
// change current working directory of the calling process to the directory specifiied
// stat, fstat, lstat


// cd [directory] or cd -

// 5. IF curpath does not begin with /
	// set curpath to PWD/curpath (if PWD does not end with /)
// 6. Delete any ./ that separates components
// 7. FOREACH .., if there is a preceding component and it is neither root nor ..
	// IF the preceding component is not a directory, then ERROR
	// the preceding component, all / separating the preceding component, .. and all / 
	// 		separating .. from the following component shall be deleted
	// remove any trailing / that are not also leading /. replace multiple non-leading
	//		consecutive / with a simple slash and replace 3 or more leading / by a single /
	//  IF curpath is then NULL -> STOP
// 8. If cupart is longueur than PATH_MAX bytes (including the terminating null) and the
//		<directory> is not longer than PATH_MAX. then curpath shall be converted from absolute pathname to relative if possible.
//		This conversion is possible if PWD with / is an initial substring of curpath
//	  Implementations  may  also  apply this conversion if curpath is not
//           longer than {PATH_MAX} bytes or the directory  operand  was  longer
//          than {PATH_MAX} bytes.
//what about removed folder?

static char	*get_directory_name(t_var *env, char **args)
{
	int		i;
	char	*directory;

	if (args[0])
	{
		if (args[1])
		{
			write (2, "cd: too many arguments\n", 24);
			return (NULL);
		}
		return (args[0]);
	}
	directory = get_value(env, HOME);
	if (!directory)
		write(2, "cd: HOME not set");
	return (ft_strdup(directory));
}

static char *try_all_cdpaths(char **cdpath, char *directory)
{
	char	*curpath;
	DIR		*dir;

	while (*cdpath)
	{
		curpath = ft_strjoin3(cdpath, "/", directory);
		dir = opendir(curpath);
		if (errno && errno != ENOENT)
		{
			perror(directory);
			free(curpath);
			return (NULL)
		}
		if (!errno)
		{
			closedir(dir);
			return (curpath);
		}
		free(curpath);
		cdpath++;
	}
	curpath = ft_strjoin("./", directory));
	dir = opendir(curpath);
	if (errno && errno != ENOENT)
	{
		perror(directory);
		free(curpath);
		return (NULL)
	}
	closedir(dir);
	return (curpath);
}

static char	*get_curpath_from_cdpath(t_env *env, char *directory)
{
	int	i;
	char	**cdpath;
	char	*ret;

	ret = get_value(env, "CDPATH");
	if (!ret)
		return (NULL);
	cdpath = ft_split(ret, ':');
	free(ret);
	if (!cdpath)
		return (NULL);
	ret = try_all_cdpaths(cdpath, directory));
	free_char_tab(cdpath);
	return (ret);
}

static int	go_and_change_var(t_var_list *env_var, char *pwd, char *curpath)
{
	int	ret;

	ret = chdir(curpath);
	if (ret)
	{
		perror("cd");
		free(pwd);
		free(cur_path);
		return (ret);
	}
	ret = change_var_by_val(env_var, "OLDPWD", pwd);
	free(pwd);
	if (ret)
	{
		free(curpath);
		return (1);
	}
	ret = change_var_by_val(env_var, "PWD", curpath);
	free(curpath);
	return (ret);
}

canonical_conversion(curpath)
{
	int		i;
	char	*tmp;
	char	*start;

	while (curpath[i])
	{
		if (curpath[i] == '.' && curpath[i + 1] == '/')
		{
			start = ft_substr(curpath, 0, i);
			tmp = ft_strjoin(start, curpath + i + 2);
			free(start);
			free(curpath);
			curpath = tmp;
		}
		if (curpath[i] == '.' && curpath[i + 1] == '.')
		{

		}
		i++;
	}
}

int	cd(t_env *env, char	**args)
{
	char	*directory;
	char	*curpath;
	char	*pwd;
	int		ret;

	directory = get_directory_name(args, env);
	if (!directory)
		return (1);
	curpath = directory;
	if (directory[0] != '/' && directory[0] != '.')
	{
		curpath = get_curpath_from_cdpath(directory, env);
		free(directory);
		if (!cur_path)
			return (1);
	}
	pwd = get_value(env, "PWD");
	if (curpath[0] != '/' && pwd)
	{
		directory = ft_strjoin3(pwd, "/", curpath);
		free(curpath);
		curpath = directory;
		if (!directory)
		{
			free(pwd);
			return (1);
		}
	}
	directory = canonical_conversion(curpath);
	//path_max
	return (go_and_change_var(env->env_var, pwd, curpath));
}