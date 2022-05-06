/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:39:55 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 15:41:32 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "env.h"
# include "parser.h"

# define TMP "/tmp/fesjfijse;oe"

int	redir_and_assign(t_env *env, t_cmd	*cmd, t_var_list *list);
int	here_doc(t_env *env, char *delimiter, int fd);

#endif