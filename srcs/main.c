/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/09 17:58:36 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include "minishell.h"

int	g_last_return = 0;

static void	handle_input(t_env *env, t_list **parser, t_lexer *lexer)
{
	if (complete_command(lexer, parser) == VALIDATED)
	{
		if (!expand_commands(env, parser))
			g_last_return = exec_commands(env, *parser, lexer);
		else
			g_last_return = 1;
	}
	else
		g_last_return = 1;
	delete_parser(parser);
}

static int	interactive_shell(t_env *env, t_list **parser, t_lexer *lexer)
{
	char	*usr_input;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	usr_input = readline(COLOR_ORANGE PS1 COLOR_RESET);
	while (usr_input)
	{
		add_history(usr_input);
		feed_lexer(lexer, usr_input);
		handle_input(env, parser, lexer);
		if (g_last_return == 130)
			usr_input = readline(NULL);
		else
			usr_input = readline(COLOR_ORANGE PS1 COLOR_RESET);
	}
	free(usr_input);
	clear_history();
	write(1, "exit\n", 5);
	return (g_last_return);
}

int	main(int argc, char	*argv[], char *envp[])
{
	t_lexer	*lexer;
	t_list	*parser;
	t_env	env;
	int		ret;

	(void)argc;
	(void)argv;
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
		ret = interactive_shell(&env, &parser, lexer);
	free_lexer(lexer);
	free_env(&env);
	return (ret);
}
