/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/02 13:44:27 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include "parser.h"
#include "env.h"
#include "minishell.h"

//update last return
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
			expand_commands(parser, env);
			print_parser(parser);
		}
		delete_parser(parser);
		usr_input = readline(PS1);
	}
	clear_history();
	write(1, "exit\n", 5);
	return (0);
}

#include "builtins.h"
int	main(int argc, char	*argv[], char *envp[])
{
	//t_lexer	*lexer;
	//t_list	*parser;
	t_env	env;
	int		ret;

	if (!init_env(&env, 10, envp))
		return (1);
	(void)argc;
	ret = export(argv + 1, &env);
	/*lexer = malloc(sizeof(t_lexer));
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
	free_lexer(lexer);*/
	free_env(&env);
	return (ret);
}
