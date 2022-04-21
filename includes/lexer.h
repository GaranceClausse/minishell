/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:28:58 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/21 11:27:36 by gclausse         ###   ########.fr       */
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
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
	PIPE,
	WORD,
	NLINE,
	ENDOF,
	EXPANSION,
	UNINITIALIZED
}	t_type;

typedef struct s_token {
	t_type			type;
	char			*content;
}	t_token;

typedef struct s_lexer {
	t_token	*token;
	int		index;
	char	*str;
}	t_lexer;

int		is_in_set(char c, char *str);
int		is_special(char c);
int		search_for_char(char c, char *str);
int		search_for_special(char *str);
int		fill_token(t_token *token, char c, int j, t_lexer *lexer);
t_token	*get_token(t_lexer *lexer);
void	feed_lexer(t_lexer *lexer, char *str);
void	delete_token(void *token);
t_token	*pick_token(t_lexer	*lexer);

#endif
