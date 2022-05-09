/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:53:22 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/09 17:26:39 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR_ORANGE     "\033[38;5;208m"
# define COLOR_RESET   "\x1b[0m"
# define PS1 "minishell > "

# include "expand.h"
# include "redirection.h"
# include "exec.h"

#endif
