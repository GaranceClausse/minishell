/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:29:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/11 22:18:08 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"
# include "exec.h"

struct					s_combo;
typedef struct s_combo	t_combo;

int		echo(char **args);
int		pwd(void);
int		print_env(t_var_list *env_var, char **args);
int		unset(t_env *env, char **args);
int		export(t_env *env, char **args);
char	*get_curpath_from_cdpath(t_env *env, char *directory);
int		check_folder_exists(char *directory, char *cmd_name, int print);
char	*canonical_conversion(char	*curpath, char *cmd_name);
int		cd(t_env *env, char	**args);
void	exit_builtin(t_combo *combo, char **args, int is_in_pipe);
int		print_export(t_var_list *env_var);

#endif