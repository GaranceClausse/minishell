/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:22:52 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/14 10:23:13 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*cpy;

	i = 0;
	if (!s)
		return (NULL);
	if (len <= ft_strlen(s))
		cpy = malloc(sizeof(char) * (len + 1));
	else
		cpy = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!cpy)
		return (NULL);
	if (start > ft_strlen(s))
	{
		cpy[0] = '\0';
		return (cpy);
	}
	while (s[start] && i < len)
	{
		cpy[i] = s[start];
		i++;
		start++;
	}
	cpy[i] = '\0';
	return (cpy);
}
