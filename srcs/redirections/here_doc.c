/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:24:25 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/03 11:43:46 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

extern int	g_last_return;

int	here_doc(char *delimiter, int fd)
{
	char	*usr_input;
	void	*old_getc;
	int		tmp;

	tmp = g_last_return;
	g_last_return = 0;
	if (fd == -1)
		return (1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	old_getc = rl_getc_function;
	rl_getc_function = getc;
	write(1, "here_doc > ", 12);
	usr_input = readline(NULL);
	while (g_last_return != 130 && usr_input
		&& ft_strcmp(usr_input, delimiter) != 0)
	{
		write(1, "here_doc > ", 12);
		write(fd, usr_input, ft_strlen(usr_input));
		write(fd, "\n", 1);
		free(usr_input);
		usr_input = readline(NULL);
	}
	free(usr_input);
	rl_getc_function = old_getc;
	if (g_last_return)
		return (1);
	g_last_return = tmp;
	if (!usr_input)
	{
		printf("unexpected end of file (wanted '%s')\n", delimiter);
		return (1);
	}
	return (0);
}
