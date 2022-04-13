/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:10 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/13 18:45:19 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	on_sigint(int signal)
{
	(void)signal;

 	write(1, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);
    rl_redisplay();
}

void	on_sigquit(int signal)
{
	(void)signal;
	return;
}

int main(int argc, char	*argv[], char *env[])
{
	char	*usr_input;
	(void)argc;
	(void)argv;
	(void)env;
	(void)	usr_input;
	signal(SIGINT, on_sigint);
	signal(SIGQUIT, on_sigquit);
	usr_input = readline("minishell > ");
	while (usr_input)
	{
		//handle input
		//history
		add_history(usr_input);
		free(usr_input);
		usr_input = readline("minishell > ");
		
	}	
}