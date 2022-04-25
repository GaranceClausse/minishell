/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:16:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/21 17:30:42 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "libft.h"
# include "lexer.h"

typedef struct s_cmd {
	t_list	*word_list;
	t_list	*token_list;
	int		is_in_pipe;
	int		fd_in;
	int		fd_out;
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
int		io_redirect(t_lexer *lexer, t_cmd *cmd);
int		word_or_assign(t_lexer *lexer, t_cmd *cmd);
int		command(t_lexer *lexer, t_cmd *cmd);
int		pipeline(t_lexer *lexer, t_list **parser);
int		complete_command(t_lexer *lexer, t_list **parser);
int	syntax_error(char *err_msg, int is_freable);

#endif
