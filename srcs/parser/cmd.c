#include "parser.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->word_list = NULL;
	cmd->token_list = NULL;
	cmd->is_in_pipe = 1;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	return (cmd);
}

void	delete_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = (void *)cmd_void;

	if (cmd->word_list)
		ft_lstclear(&cmd->word_list, delete_token);
	if (cmd->token_list)
		ft_lstclear(&cmd->token_list, delete_token);
	free(cmd);
}

t_cmd	*feed_cmd(t_lexer *lexer)
{
	(void)lexer;
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);

	//call grammar and check command
	return (cmd);
}

int	add_token(t_list **token_list, t_token *token)
{
	t_list *new;

	new = ft_lstnew((void *)token);
	if (!new)
		return (1);
	ft_lstadd_back(token_list, new);
	return (0);
}
