/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:24:21 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/26 17:17:53 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_end_index(char const *s, char const *set)
{
	int	end;

	end = ft_strlen(s) - 1;
	while (end > 0 && ft_is_in_set(s[end], set))
		end--;
	if (end >= 0)
		end++;
	return (end);
}

static int	get_start_index(char const *s, char const *set)
{
	int	start;

	start = 0;
	while (s[start] && ft_is_in_set(s[start], set))
		start++;
	return (start);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		start;
	int		end;
	size_t	len;

	if (! s || !set)
		return (NULL);
	start = get_start_index(s, set);
	end = get_end_index(s, set);
	if (start >= end)
		return (ft_strdup(""));
	len = end - start;
	return (ft_substr(s, start, len));
}