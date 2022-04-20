#include "libft.h"
#include "lexer.h"

typedef struct	s_cmd {
	t_list	*word_list;
	t_list	*token_list;
	int		is_in_pipe;
	int		fd_in;
	int		fd_out;
}			t_cmd;

void	delete_parser(t_list **parser);
t_cmd	*feed_cmd(t_lexer *lexer);
int		add_cmd(t_list **parser, t_cmd *cmd);
void	delete_cmd(void *cmd);
int		add_token(t_list **token_list, t_token *token);