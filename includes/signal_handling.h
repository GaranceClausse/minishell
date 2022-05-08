/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:28:16 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/08 18:54:01 by deacllock        ###   ########.fr       */
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

#endif