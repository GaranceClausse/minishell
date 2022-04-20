/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:28:58 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/15 16:08:22 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>

typedef enum e_type {
	ASSIGNMENT,
	REDIRECTION,
	PIPE,
	WORD,
	NLINE,
	ENDOF,
	EXPANSION,
	ERROR
}	t_type;

typedef struct s_token {
	t_type			type;
	char			*content;
}	t_token;

typedef struct s_lexer {
	t_token	token;
	int		index;
	char	*str;
}	t_lexer;

int		is_in_set(char c, char *str);
int		is_special(char c);
int		search_for_char(char c, char *str);
int		search_for_special(char *str);
t_token	get_token(t_lexer *lexer);
void	feed_lexer(t_lexer *lexer, char *str);
void	tokenize_input(char *str);
void	delete_token(void *token);

#endif
