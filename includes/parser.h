/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:16:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/08 18:16:47 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "lexer.h"
# include "signal_handling.h"

typedef struct s_cmd {
	t_list	*wordlist;
	t_list	*token_list;
	int		is_in_pipe;
	int		fd_in;
	int		fd_out;
	int		pid;
}			t_cmd;

typedef enum e_ret {
	SYNTAX_ERROR,
	ERROR,
	VALIDATED,
	NOT_VALIDATED
}	t_ret;

void	delete_parser(t_list **parser);
int		add_cmd(t_list **parser, t_cmd *cmd);
void	delete_cmd(void *cmd);
int		add_token(t_list **token_list, t_token *token);
void	print_parser(t_list	**parser);
void	print_token(t_list	**token_list);
t_cmd	*init_cmd(void);
int		linebreak(t_lexer *lexer, int is_final);
int		prefix_suffix(t_lexer *lexer, t_cmd *cmd, int is_prefix);
int		command(t_lexer *lexer, t_cmd *cmd);
int		pipeline(t_lexer *lexer, t_list **parser);
int		complete_command(t_lexer *lexer, t_list **parser);
int		syntax_error(char *err_msg, int is_freable);

#endif
