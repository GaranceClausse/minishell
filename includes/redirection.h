/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:39:55 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/03 16:47:59 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "signal_handling.h"
# include "builtins.h"

int	here_doc(t_env *env, char *delimiter, int fd);

#endif