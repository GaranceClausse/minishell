/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:39:55 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/03 14:44:02 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "env.h"
# include "parser.h"

int	redir_and_assign(t_env *env, t_cmd *cmd);
int	here_doc(char *delimiter, int fd);

#endif