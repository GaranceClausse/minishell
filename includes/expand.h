/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:07:20 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/26 16:10:10 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

#include "parser.h"

char	**ft_split(const char *str, char *iss);
int		spliter(t_cmd *cmd);
int 	expand_commands(t_list **parser);

#endif