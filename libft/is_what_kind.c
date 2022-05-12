/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_what_kind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:15:39 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/12 13:24:47 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (0);
	else
		return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else
		return (1);
}

int	ft_isunderscore(int c)
{
	if (c == '_')
		return (0);
	else
		return (1);
}

int	is_valid_identifier(char *str, char *arg)
{
	int		i;
	int		pbm;
	char	*msg;

	i = 0;
	pbm = 0;
	while (arg[i] && (i == 0 || arg[i] != '='))
	{
		if ((ft_isalnum(arg[i]) && ft_isunderscore(arg[i]) && arg[i] != '=')
			|| ft_isdigit(arg[0]) == 0 || arg[0] == '=')
					pbm++;
		i++;
	}
	if (pbm != 0 || !ft_strcmp(arg, ""))
	{
		msg = ft_strjoin3(str, ": '", arg);
		if (!msg)
			return (1);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(msg);
		return (1);
	}
	return (0);
}
