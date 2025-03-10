/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:08:53 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/12 15:45:33 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(void)
{
	char	*cur_dir;
	char	*buf;

	buf = NULL;
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
