/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:03:56 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/26 11:15:59 by vkrajcov         ###   ########.fr       */
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
int		search(t_var_list *dst, char *var_name);
int		add_var(t_env *env, t_var_list *dst, char *var); 
char	*delete_var(t_env *env, char *var_name);

#endif
