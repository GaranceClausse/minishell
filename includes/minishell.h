/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:53:22 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/04 15:15:20 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR_ORANGE     "\033[38;5;208m"
# define COLOR_RESET   "\x1b[0m"
# define BOLD "\e[1;37m"
# define FIRE 
# define PS1 COLOR_ORANGE"minishell > "COLOR_RESET

# include "expand.h"
# include "redirection.h"
# include "exec.h"

typedef struct s_combo {
	t_list	**parser;
	t_env	*env;
	t_lexer	*lexer;
}	t_combo;

#endif
