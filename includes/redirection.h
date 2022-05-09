/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:39:55 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/09 17:28:14 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "expand.h"

# define TMP "/tmp/fesjfijse;oe"

int	here_doc(t_env *env, char *delimiter, int fd);
int	assign(t_env *env, t_cmd *cmd, t_var_list *list);
int	redir(t_env *env, t_cmd	*cmd);

#endif