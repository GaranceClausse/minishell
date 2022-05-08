/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:07:20 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/08 21:48:27 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "parser.h"
# include "env.h"

typedef struct	s_split
{
	int	count_word;
	int	is_s_quote;
	int	is_d_quote;
}	t_split;

char	**iss_split(const char *str, char *iss);
int		split_list(t_list **list);
void	search_and_expand(t_cmd	*cmd, t_env *env);
void	remove_empty_cmds(t_list **list);
void	remove_empty_tokens(t_list **list);
int		remove_quotes(t_list **list);
char	*search_var(t_var_list *dst, char *var_name, int j);
int		expand_commands(t_env *env, t_list **parser);

#endif