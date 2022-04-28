/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:29:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/28 17:28:11 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env.h"

int	pwd(char **args);
int	print_env(char **args, t_var_list *env_var);
int	unset(char **args, t_env *env);

#endif