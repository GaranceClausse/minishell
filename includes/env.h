/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:03:56 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/05/03 14:42:15 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"

typedef struct s_var_list
{
	int		size;
	int		max;
	char	**list;
}	t_var_list;

typedef struct s_env
{
	int			last_return;
	t_var_list	shell_var;
	t_var_list	env_var;
}	t_env;

void	free_env(t_env *env);
t_env	*init_env(t_env *env, int max, char *envp[]);
int		search_in_env(t_var_list *dst, char *var_name, int len);
char	*extract_name(char *var);
char	*extract_var_value(char *var);
int		change_var(t_var_list *dst, char *var);
int		add_var(t_env *env, t_var_list *dst, char *var);
char	*delete_var(t_env *env, char *var_name);
char	*get_value(t_env *env, char *value);
int 	change_var_by_val(t_env *env,t_var_list *dst, char *var, char *val);

#endif
