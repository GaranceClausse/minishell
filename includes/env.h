/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:03:56 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/18 11:35:49 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "libft.h"

typedef struct s_var_list
{
	int		size;
	int 	max;
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
char	*search(t_env *env, char *var);
int	add_var(t_env *env, t_var_list *dst, char *var); 


//void *ft_realloc(void *ptr, size_t size);

////-> check si on doit realloc ou si ca existe deja
//
//int delete_var(s_env *env, char *var)

#endif
