/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:28:16 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/26 11:52:57 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	sigint_handler(int signo);

#endif