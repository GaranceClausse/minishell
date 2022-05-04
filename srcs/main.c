/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/04 14:19:07 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include "minishell.h"

//update last return
int	expand_and_exec_commands(t_env *env, t_list **parser)
{
	t_list	*cur;
	t_cmd	*cmd;

	cur = *parser;
	while (cur)
	{
		cmd = (t_cmd *)cur->content;
		search_and_expand(cmd, env);
		if (split_list(&cmd->wordlist) || split_list(&cmd->token_list))
			return (1);
		remove_empty_tokens(&cmd->wordlist);
		if (remove_quotes(&cmd->wordlist) || remove_quotes(&cmd->token_list))
			return (1);
		if (redir_and_assign(env, cmd)) // may be done in fork!!
			return (1);
		exec(env, cmd);
		cur = cur->next;
	}
	remove_empty_cmds(parser);
	return (0);
}
//exit error on error
//stop traping the signal when not interactive
static int	interactive_shell(t_env *env, t_list **parser, t_lexer *lexer)
{
	char	*usr_input;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	usr_input = readline(PS1);
	while (usr_input)
	{
		add_history(usr_input);
		(void)env;
		feed_lexer(lexer, usr_input);
		if (complete_command(lexer, parser) == VALIDATED)
		{
			expand_and_exec_commands(env, parser);
		//	print_parser(parser);
		}
		delete_parser(parser);
		usr_input = readline(PS1);
	}
	clear_history();
	write(1, "exit\n", 5);
	return (0);
}

int	main(int argc, char	*argv[], char *envp[])
{
	t_lexer	*lexer;
	t_list	*parser;
	t_env	env;
	int		ret;

	if (!init_env(&env, 10, envp))
		return (1);
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
	{
		free_env(&env);
		return (1);
	}
	lexer->str = NULL;
	lexer->token = NULL;
	feed_lexer(lexer, NULL);
	parser = NULL;
	ret = 0;
	if (isatty(STDIN_FILENO))
		if (argc == 1 || (argc == 2 && !ft_strcmp(argv[1], "-")))
			ret = interactive_shell(&env, &parser, lexer);
	//readfile arg 1 ou arg 2 (-)
	free_lexer(lexer);
	free_env(&env);
	return (ret);
}
