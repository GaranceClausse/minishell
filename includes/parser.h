/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:26:48 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/20 16:08:58 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

typedef struct	s_cmd {
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
} t_ret;

void	delete_parser(t_list **parser);
int		add_cmd(t_list **parser, t_cmd *cmd);
void	delete_cmd(void *cmd);
int		add_token(t_list **token_list, t_token *token);
int 	complete_command(t_lexer *lexer, t_list **parser);
void	print_parser(t_list	**parser);
void	print_token(t_list	**token_list);
t_cmd	*init_cmd(void);