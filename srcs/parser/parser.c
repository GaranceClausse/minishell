//%start  complete_command
//%%
// complete_command : command linebreak
//                  | command pipeline
//                  ; 
// pipeline		    : '|' linebreak command linebreak
//					| '|' command linebreak
//					| '|' linebreak command pipeline
//					| '|' command pipeline
//                  ;
// command  		: cmd_cpl WORD cmd_cpl
//                  | cmd_cpl WORD
//                  | cmd_cpl
//                  | WORD cmd_cpl
//                  | WORD
//                  ;
// cmd_cpl          : io_redirect 	  cmd_cpl
//                  | ASSIGNMENT_WORD cmd_cpl
//                  | WORD		      cmd_cpl
//					| io_redirect
//                  | ASSIGNMENT_WORD
//                  | WORD
//					;
// io_redirect      : '<'       WORD
//                  | '>'       WORD
//                  | DGREAT    WORD
// 			        | DLESS     WORD 
//                  ;
// linebreak		: 			   NEWLINE
//					: newline_list NEWLINE
//                  ;

//bash --posix

#include "parser.h"

int	add_cmd(t_list **parser, t_cmd *cmd)
{
	t_list	*new;
	void	*cmd_void;

	cmd_void = (void *)cmd;
	new = ft_lstnew(cmd_void);
	if (!new)
	{
		delete_cmd(cmd_void);
		return (1);
	}
	ft_lstadd_back(parser, new);
	return (0);
}

void	delete_parser(t_list **parser)
{
	ft_lstclear(parser, delete_cmd);
}

int main()
{
	t_list	*parser;

	parser = NULL;
	add_cmd(&parser, feed_cmd(NULL));
	add_cmd(&parser, feed_cmd(NULL));
	delete_parser(&parser);
	
	return (0);
}