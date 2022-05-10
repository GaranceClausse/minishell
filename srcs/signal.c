/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:26:52 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/10 15:55:08 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handling.h"

void	sigint_handler(int signo)
{
	(void)signo;
	g_last_return = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_multiline(int signo)
{
	(void)signo;
	g_last_return = 130;
	write(1, "\n", 1);
}
