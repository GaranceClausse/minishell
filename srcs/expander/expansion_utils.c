/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:11:12 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/09 11:13:08 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"


void	shall_i_expand(char c, int *s_quote, int *d_quote)
{
	if (c == '\"' && *s_quote % 2 == 0)
			(*d_quote)++;
	else if (c == '\'' && *d_quote % 2 == 0)
			(*s_quote)++;
}

char	*search_var(t_var_list *dst, char *var_name, int j)
{
	int	index;

	index = search_in_env(dst, var_name, j - 1);
	if (j == 1)
		return (ft_strdup("$"));
	else if (index == -1)
		return (ft_strdup(""));
	else
		return (extract_var_value(dst->list[index]));
}

char	*get_str_expand(t_env *env, t_token *token, int *i, int *j)
{
	char	*str_expand;

	if (token->content[(*i) + 1] && token->content[(*i) + 1] == '?')
	{
		str_expand = ft_itoa(g_last_return);
		(*j)++;
	}
	else
	{
		str_expand = search_var(&env->env_var, &token->content[(*i) + 1], *j);
		if (str_expand && ft_strcmp(str_expand, "") == 0)
		{
			free(str_expand);
			str_expand = search_var(&env->shell_var,
					&token->content[(*i) + 1], *j);
		}
	}
	return (str_expand);
}
