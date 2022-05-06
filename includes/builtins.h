/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:29:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 11:51:16 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env.h"
#include "exec.h"

struct s_combo;
typedef	struct s_combo t_combo;

int		echo(char **args);
int		pwd(char **args);
int		print_env(t_var_list *env_var, char **args);
int		unset(t_env *env, char **args);
int		export(t_env *env, char **args);
char	*get_curpath_from_cdpath(t_env *env, char *directory);
int		check_folder_exists(char *curpath, char *directory);
char	*canonical_conversion(char	*curpath);
int		cd(t_env *env, char	**args);
void	exit_builtin(t_combo *combo, char **args);
int		print_export(t_var_list *env_var);

#endif