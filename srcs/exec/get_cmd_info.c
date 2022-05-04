/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:28:09 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 15:57:16 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


static char	**get_paths(t_env *env)
{
	char	*path;
	char	**path_list;

	path = get_value(env, "PATH");
	if (!path)
		return (NULL);
	path_list = ft_split(path, ':');
	free(path);
	return (path_list);
}

char	*get_cmd_name(t_env *env, char *partial_cmd)
{
	char	**paths;
	char	*cmd;
	int		i;

	i = 0;
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		cmd = ft_strjoin3(paths[i], "/", partial_cmd);
		if (!cmd)
		{
			free_char_tab(paths, 0);
			return (NULL);
		}
		if (!access(cmd, F_OK))
		{
			free_char_tab(paths, 0);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	free_char_tab(paths, 0);
	return (NULL);
}

char	**token_to_wordlist(t_list *token_list)
{
	t_token	*cur;
	char	**wordlist;
	int		i;

	i= 0;
	wordlist = malloc(sizeof(char *) * (ft_lstlen(token_list) + 1));
	if (!wordlist)
		return (NULL);
	while (token_list)
	{
		cur = (t_token *)token_list->content;
		wordlist[i] = ft_strdup(cur->content);
		if (!wordlist[i])
		{
			free_char_tab(wordlist, 0);
			return (NULL);
		}
		token_list = token_list->next;
		i++;
	}
	wordlist[i] = NULL;
	return (wordlist);
}
