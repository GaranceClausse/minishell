/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:11:12 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/09 17:28:47 by gclausse         ###   ########.fr       */
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

char	*search_var(t_env *env, char *var_name, int j)
{
	int	index;

	if (j == 1)
		return (ft_strdup("$"));
	index = search_in_env(&env->shell_var, var_name, j - 1);
	if (index == -1)
	{
		index = search_in_env(&env->env_var, var_name, j - 1);
		if (index == -1)
			return (ft_strdup(""));
		return (extract_var_value(env->env_var.list[index]));
	}
	return (extract_var_value(env->shell_var.list[index]));
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
		str_expand = search_var(env, &token->content[(*i) + 1], *j);
	return (str_expand);
}
