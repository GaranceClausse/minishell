/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:28:09 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/12 19:15:43 by gclausse         ###   ########.fr       */
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
	path_list = ft_split(path, ":");
	free(path);
	return (path_list);
}

int	get_cmd_name(t_env *env, char **partial_cmd)
{
	char	**paths;
	char	*cmd;
	int		i;

	i = 0;
	paths = get_paths(env);
	if (!paths)
		return (1);
	while (paths[i])
	{
		cmd = ft_strjoin3(paths[i], "/", *partial_cmd);
		if (!cmd || !access(cmd, X_OK))
		{
			free_char_tab(paths, 0);
			if (!cmd)
				return (1);
			free(*partial_cmd);
			*partial_cmd = cmd;
			return (-1);
		}
		free(cmd);
		i++;
	}
	free_char_tab(paths, 0);
	return (0);
}

char	**token_to_wordlist(t_list *token_list)
{
	t_token	*cur;
	char	**wordlist;
	int		i;

	i = 0;
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

char	**get_wordlist(t_combo *combo, t_cmd *cmd)
{
	char	**wordlist;

	wordlist = token_to_wordlist(cmd->wordlist);
	if (!wordlist)
	{
		if (cmd->is_in_pipe)
		{
			free_before_exit(combo, 0);
			exit(1);
		}
		return (NULL);
	}
	return (wordlist);
}
