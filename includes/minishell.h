/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:53:22 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/11 22:50:29 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR_ORANGE     "\1\033[38;5;208m\2"
# define COLOR_RESET   "\1\x1b[0m\2"
# define PS1 "minishell > "

# include "expand.h"
# include "redirection.h"
# include "exec.h"

#endif
