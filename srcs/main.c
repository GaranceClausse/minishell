/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/21 11:30:30 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include "parser.h"
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

/*
void	tokenize_input(char *str)
{
	t_token	token;
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	feed_lexer(lexer, str);
	token = get_token(lexer);
	while (token.content != NULL)
	{
		printf("token.content = %s\n", token->content);
		printf("token.type = %u\n\n", token->type);
		token = get_token(lexer);
	}
		feed_lexer(lexer, usr_input);
		cmd = feed_cmd(lexer);
		if (!cmd)
		{
			write(1, "pas content\n", 12);
			break;
		}
		if (!add_cmd(parser, cmd))
		{
			printf("Pas content mais parser");
			break;
		}
		print_parser(parser);
		//parse input
}*/

int	interactive_shell(t_lexer *lexer, t_list **parser)
{
	char	*usr_input;
	//t_cmd	*cmd;
	//signal(SIGINT, sighandler); //issue with infinite loop
	signal(SIGQUIT, SIG_IGN);
	usr_input = readline(PS1);
	while (usr_input)
	{
		//tokenize_input(usr_input);
		//parse input
		add_history(usr_input);
		feed_lexer(lexer, usr_input);
		complete_command(lexer, parser);
		//add_cmd(parser, cmd);
		print_parser(parser);
		free(usr_input);
		usr_input = readline(PS1);
		delete_parser(parser);
	}
	free(usr_input);
	clear_history();
	write(1, "exit\n", 5);
	return (0);
}

int	main(int argc, char	*argv[], char *env[])
{
	t_lexer	*lexer;
	t_list	*parser;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (1);
	parser = NULL;
	(void)env;
	if (isatty(STDIN_FILENO))
		if (argc == 1 || (argc == 2 && !ft_strcmp(argv[1], "-")))
			return (interactive_shell(lexer, &parser));
	//readfile arg 1 ou arg 2 (-)
}
