/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/14 16:48:16 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void	interactive_shell(void)
{
	char				*usr_input;
	
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	
	usr_input = readline(PS1);
	while (usr_input)
	{
		(void)	usr_input; //handle input
		add_history(usr_input);
		free(usr_input);
		usr_input = readline(PS1);	
	}
	free(usr_input);
	clear_history();
	write(1, "exit\n", 5);
}

int main(int argc, char	*argv[], char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;
	// or is a tty
	//if (argc == 0 || argc == 1 && !ft_strcmp(argv[1], "-"))
	interactive_shell();
	// -c -> read commands from the first non option argument command string
	// pipe file ->is a tty
	// -
	// file -> is a tty
	// -i interactive
}

//save in file! ->persistance