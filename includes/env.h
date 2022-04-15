/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:03:56 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/15 18:21:07 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

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


#endif