/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:07:20 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/26 17:08:20 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
#include "parser.h"
#include "env.h"

#include "parser.h"

char	**ft_split(const char *str, char *iss);
int		split_list(t_list **list);
int 	expand_commands(t_list **parser, t_env *env);
int		expansion(t_cmd	*cmd, t_env *env);

#endif