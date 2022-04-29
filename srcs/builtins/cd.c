/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:33:50 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/29 18:10:48 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <error.h>
#include <unistd.h>
#include "env.h"
#include "libft.h"

char	*get_directory_name(t_env *env, char **args)
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

char *try_all_cdpaths(char **cdpath, char *directory)
{
	char	*curpath;
	int		ret;

	while (*cdpath)
	{
		curpath = ft_strjoin3(*cdpath, "/", directory);
		ret = check_folder_exists(curpath, directory);
		if (ret == -1 || ret == 1)
		{
			if (ret == 1)
				return (curpath);
			free(curpath);
			return (NULL);
		}
		free(curpath);
		cdpath++;
	}
	curpath = ft_strjoin("./", directory);
	ret = check_folder_exists(curpath, directory);
	if (ret == 1)
		return (curpath);
	free(curpath);
	if (ret == 0)
		return (ft_strdup(directory));
	return (NULL);
}

char	*get_curpath_from_cdpath(t_env *env, char *directory)
{
	char	**cdpath;
	char	*ret;

	ret = get_value(env, "CDPATH"); //how can we know it failed
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

char *join_pwd_to_path(char *pwd, char *curpath)
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

int	remove_substr(char **str, int start, int end)
{
	char	*new;
	char	*first;
	
	first = ft_substr(*str, 0, start);
	if (!first)
		return (1);
	new = ft_strjoin(first, *str + end);
	free(first);
	if (!new)
		return (1);
	free(*str);
	*str = new;
	return (0);
}

void delete_from_char_tab(char **tab, int index)
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

char	*canonical_conversion(char	*curpath)
{
	char	**split;
	char	*canon_path;
	char	*tmp;
	int		i;
	int		ret;

	split = ft_split(curpath, '/');
	if (!split)
		return (NULL);
	i = 0;
	canon_path = ft_strdup("/");
	while (split[i])
	{
		printf("%s\n", split[i]);
		if (!ft_strcmp(split[i], ".."))
		{
			if (!i && ft_strcmp(canon_path, "/"))
			{
				free(canon_path);
				canon_path = ft_strdup("/");
				continue;
			}
			ret = check_folder_exists(canon_path, curpath);
			if ( ret != 1)
			{
				if (!ret)
					perror(curpath);
				free(canon_path);
				free_char_tab(split, 0);
				return (NULL);
			}
			canon_path[ft_strlen(canon_path) - ft_strlen(split[i - 1]) - 1] = '\0';
			delete_from_char_tab(split, i);
			delete_from_char_tab(split, i - 1);
			i--;
		}
		else if (!ft_strcmp(split[i], "."))
			delete_from_char_tab(split, i);
		else
		{
			tmp = ft_strjoin3(canon_path, split[i], "/");
			free(canon_path);
			if (!tmp)
			{
				free_char_tab(split, 0);
				return (NULL);
			}
			canon_path = tmp;
			i++;
		}
	}
	free_char_tab(split, 0);
	return (canon_path);
}

/*
int	go_and_change_var(t_var_list *env_var, char *pwd, char *curpath)
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


*/
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
	if (!directory)
	{
		free(curpath);
		return (1);
	}
	curpath = directory;
	printf("curpath = %s\n", curpath);
	//return (go_and_change_var(env->env_var, pwd, curpath));
	free(curpath);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	t_env	env;

	init_env(&env, 10, envp);
	cd(&env, argv + 1);
	free_env(&env);
}