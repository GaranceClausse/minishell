/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:59:20 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/08 21:41:31 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	x;
	char	*str;

	i = 0;
	str = (char *)s;
	x = (char)c;
	if (c == '\0')
		return (&str[i + ft_strlen(str)]);
	while (str[i] && str[i] != x)
		i++;
	if (str[i] != '\0')
		return (&str[i]);
	else
		return (NULL);
}
