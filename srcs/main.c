/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/06/08 14:52:38 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include "minishell.h"

int	g_last_return = 0;

static void	handle_input(t_env *env, t_list **parser, t_lexer *lexer)
{
	int	ret;

	if (complete_command(lexer, parser) == VALIDATED)
	{
		ret = expand_commands(env, parser);
		if (!ret)
			g_last_return = exec_commands(env, *parser, lexer);
		else
			g_last_return = ret;
	}
	else if (g_last_return < 128)
		g_last_return = 2;
	delete_parser(parser);
}

static int	interactive_shell(t_env *env, t_list **parser, t_lexer *lexer)
{
	char	*usr_input;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	usr_input = readline(COLOR_ORANGE PS1 COLOR_RESET);
	signal(SIGINT, SIG_IGN);
	while (usr_input)
	{
		add_history(usr_input);
		feed_lexer(lexer, usr_input);
		handle_input(env, parser, lexer);
		signal(SIGINT, sigint_handler);
		usr_input = readline(COLOR_ORANGE PS1 COLOR_RESET);
		signal(SIGINT, SIG_IGN);
	}
	free(usr_input);
	clear_history();
	ft_putstr_fd("exit\n", 2);
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
	lexer = init_lexer();
	if (!lexer)
	{
		free_env(&env);
		return (1);
	}
	parser = NULL;
	ret = 0;
	if (isatty(STDOUT_FILENO))
		ret = interactive_shell(&env, &parser, lexer);
	free_lexer(lexer);
	free_env(&env);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (ret);
}
