/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:39:55 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/03 16:51:47 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "parser.h"
# include "env.h"

int	here_doc(t_env *env, char *delimiter, int fd);
int	redir_and_assign(t_env *env, t_cmd	*cmd);

#endif