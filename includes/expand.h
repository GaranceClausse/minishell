/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:07:20 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/27 14:57:18 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "parser.h"
# include "env.h"

char	**iss_split(const char *str, char *iss);
int		split_list(t_list **list);
int		expand_commands(t_list **parser, t_env *env);
void	search_and_expand(t_cmd	*cmd, t_env *env);
void	remove_empties(t_list **list);
int		remove_quotes(t_list **list);

#endif