/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:07:20 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/12 09:35:19 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "parser.h"
# include "env.h"

char	**iss_split(const char *str, char *iss);
int		split_list(t_list **list);
void	search_and_expand(t_cmd	*cmd, t_env *env);
void	remove_empty_cmds(t_list **list);
void	remove_empty_tokens(t_list **list);
int		remove_quotes(t_list **list);
char	*search_var(t_env *env, char *var_name, int j);
void	shall_i_expand(char c, int *s_quote, int *d_quote);
char	*get_str_expand(t_env *env, t_token *token, int *i, int *j);
int		expand_commands(t_env *env, t_list **parser);
void	search_and_expand_redir(t_cmd	*cmd, t_env *env);

#endif