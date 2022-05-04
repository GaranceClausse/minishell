/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:22:56 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 13:58:52 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "builtins.h"
#include "parser.h"

char	**token_to_wordlist(t_list *token_list);
int		is_builtin(char *cmd_name);
int		exec_builtin(t_env *env, char **wordlist);
char	*get_cmd_name(t_env *env, char *partial_cmd);
int		exec(t_env *env, t_cmd *cmd);

#endif