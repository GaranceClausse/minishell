/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:28:58 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/13 16:33:17 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum {
	WORD,
	ASSIGNMENT,
	REDIRECTION,
	PIPE,
	NEWLINE,
	ENDOF,
	EXPANSION,
	ERROR

}	t_type;

typedef struct s_token {
	t_type	type;
	char *content;
}	t_token;


