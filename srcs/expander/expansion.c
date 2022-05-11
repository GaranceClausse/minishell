/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:48:35 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/11 21:22:09 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	create_new_token(t_token *token, t_env *env, int i, int j)
{
	char	*tmp;
	char	*str_expand;
	char	*str_base;
	int		ret;

	str_expand = get_str_expand(env, token, &i, &j);
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
		shall_i_expand(token->content[i], &s_quote, &d_quote);
		if (token->content[i] == '$' && (s_quote % 2 == 0))
		{
			j = 1;
			while (token->content[j + i]
				&& (ft_isalnum(token->content[j + i]) == 0
					|| ft_isunderscore(token->content[j + i]) == 0))
				j++;
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

	list = cmd->wordlist;
	while (list)
	{
		token = list->content;
		if (token->type != HERE_DOC)
			expand_var(token, env);
		list = list->next;
	}
}


void	search_and_expand_redir(t_cmd	*cmd, t_env *env)
{
	t_token	*token;
	t_list	*list;

	list = cmd->token_list;
	while (list)
	{
		token = list->content;
		if (token->type != HERE_DOC)
			expand_var(token, env);
		list = list->next;
	}
}
