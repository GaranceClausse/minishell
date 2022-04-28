/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:26:52 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/26 11:52:47 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handling.h"

extern int	g_is_sigint;

void	sigint_handler(int signo)
{
	(void)signo;

	g_is_sigint = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}