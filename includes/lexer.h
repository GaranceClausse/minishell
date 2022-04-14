/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:28:58 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/14 10:50:18 by gclausse         ###   ########.fr       */
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

typedef enum {
	ASSIGNMENT,
	REDIRECTION,
	PIPE,
	WORD,
	NEWLINE,
	ENDOF,
	EXPANSION,
	ERROR

}	t_type;

typedef struct s_token {
	t_type	type;
	char *content;
}	t_token;

#endif
