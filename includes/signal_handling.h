/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:28:16 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/10 15:47:33 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <unistd.h>

extern int	g_last_return;
void	sigint_handler(int signo);
void	sigint_handler_multiline(int signo);

#endif