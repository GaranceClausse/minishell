/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:08:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/11 14:18:51 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(char **args)
{
	char	*cur_dir;
	char	*buf;

	buf = NULL;
	if (*args)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	cur_dir = getcwd(buf, 4096);
	if (cur_dir == NULL)
	{
		ft_putstr_fd("pwd: path not found\n", 2);
		return (1);
	}
	printf("%s\n", cur_dir);
	free(cur_dir);
	return (0);
}
