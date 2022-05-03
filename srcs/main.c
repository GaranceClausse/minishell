/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/03 16:58:27 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

//update last return
int	expand_and_exec_commands(t_list **parser, t_env *env)
{
	t_list	*cur;
	t_cmd	*cmd;

	cur = *parser;
	while (cur)
	{
		cmd = (t_cmd *)cur->content;
		search_and_expand(cmd, env);
		if (split_list(&cmd->word_list) || split_list(&cmd->token_list))
			return (1);
		remove_empty_tokens(&cmd->word_list);
		if (remove_quotes(&cmd->word_list) || remove_quotes(&cmd->token_list))
			return (1);
		if (redir_and_assign(env, cmd))
			return (1);
		cur = cur->next;
	}
	remove_empty_cmds(parser);
	return (0);
}

//exec only when no syntax error
//exit error on error
//stop traping the signal when not interactive
int	interactive_shell(t_lexer *lexer, t_list **parser, t_env *env)
{
	char	*usr_input;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	usr_input = readline(PS1);
	while (usr_input)
	{
		add_history(usr_input);
		feed_lexer(lexer, usr_input);
		if (complete_command(lexer, parser) == VALIDATED)
		{
			expand_and_exec_commands(parser, env);
			print_parser(parser);
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
			ret = interactive_shell(lexer, &parser, &env);
	//readfile arg 1 ou arg 2 (-)
	free_lexer(lexer);
	free_env(&env);
	return (ret);
}
