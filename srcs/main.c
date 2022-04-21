/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/21 13:19:50 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include "parser.h"
#include "env.h"
#include "minishell.h"

void	sighandler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//update last return
//exec only when no syntax error
//exit error on error
//stop traping the signal when not interactive
int	interactive_shell(t_lexer *lexer, t_list **parser,  t_env *env)
{
	char	*usr_input;
	(void)env;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	usr_input = readline(PS1);
	while (usr_input)
	{
		add_history(usr_input);
		feed_lexer(lexer, usr_input);
		complete_command(lexer, parser);
		print_parser(parser);
		usr_input = readline(PS1);
		delete_parser(parser);
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
	feed_lexer(lexer, NULL);
	parser = NULL;
	ret = 0;
	if (isatty(STDIN_FILENO))
		if (argc == 1 || (argc == 2 && !ft_strcmp(argv[1], "-")))
			ret = interactive_shell(lexer, &parser, &env);
	//readfile arg 1 ou arg 2 (-)
	if (lexer->token)
		delete_token(lexer);
	free(lexer);
	free_env(&env);
	return (ret);
}
