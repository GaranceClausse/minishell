/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:08:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/28 12:32:42 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(char **args)
{
	char	*cur_dir;
	char	*buf;
	t_env	*env;

	if (*args)
	{
		write (1, "pwd: too many arguments\n", 25);
		return (1);
	}
	cur_dir = getcwd(buf, 4096);
	if (cur_dir == NULL)
	{
		write (1, "pwd: path not found\n", 21);
		return (1);
	}
	write (1, cur_dir, ft_strlen(cur_dir));
	write(1, "\n", 2);
	return (0);
}
