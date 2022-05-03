/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:48:35 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/03 17:23:25 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

extern int	g_last_return;

char	*search_var(t_var_list *dst, char *var_name, int j)
{
	int	i;
	int	index;

	i = 0;
	index = search_in_env(dst, var_name, j - 1);
	if (j == 1)
		return (ft_strdup("$"));
	else if (index == -1)
		return (ft_strdup(""));
	else
		return (extract_var_value(dst->list[index]));
}

int	create_new_token(t_token *token, t_env *env, int i, int j)
{
	char	*tmp;
	char	*str_expand;
	char	*str_base;
	int		ret;

	if (token->content[i + 1] && token->content[i + 1] == '?')
	{
		str_expand = ft_itoa(g_last_return);
		j++;
	}
	else
	{
		str_expand = search_var(&env->env_var, &token->content[i + 1], j);
		if (str_expand && ft_strcmp(str_expand, "") == 0)
		{
			free(str_expand);
			str_expand = search_var(&env->shell_var, &token->content[i + 1], j);
		}
		//if (!str_expand)
		//	return (-1);
	}
	str_base = ft_substr(token->content, 0, i);
	tmp = token->content;
	token->content = ft_strjoin3(str_base, str_expand,
			token->content + (j + i));
	free(tmp);
	ret = ft_strlen(str_expand);
	free(str_base);
	free(str_expand);
	return (ret);
}

void	expand_var(t_token *token, t_env *env)
{
	int		s_quote;
	int		d_quote;
	int		i;
	int		j;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (token->content[i])
	{
		if (token->content[i] == '\"' && s_quote % 2 == 0)
			d_quote++;
		else if (token->content[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		if (token->content[i] == '$' && (s_quote % 2 == 0))
		{
			j = 1;
			while (token->content[j + i]
				&& (ft_isalnum(token->content[j + i]) == 0
					|| ft_isunderscore(token->content[j + i]) == 0))
				j++;
			//check output of create_new_token
			i += create_new_token(token, env, i, j);
		}
		else
			i++;
	}
}

void	search_and_expand(t_cmd	*cmd, t_env *env)
{
	t_token	*token;
	t_list	*list;

	list = cmd->word_list;
	while (list)
	{
		token = list->content;
		if (token->type != HERE_DOC)
			expand_var(token, env);
		list = list->next;
	}
}
