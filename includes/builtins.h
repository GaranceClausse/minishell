/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:29:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/02 17:22:04 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env.h"

int		echo(char **args);
int		pwd(char **args);
int		print_env(char **args, t_var_list *env_var);
int		unset(char **args, t_env *env);
int		export(char **args, t_env *env);
char	*get_curpath_from_cdpath(t_env *env, char *directory);
int		check_folder_exists(char *curpath, char *directory);
char	*canonical_conversion(char	*curpath);
int		cd(t_env *env, char	**args);
void	exit_builtin(char **args);
int	print_export(t_var_list *env_var);

#endif