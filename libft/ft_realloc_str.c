/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:13:52 by vkrajcov          #+#    #+#             */
/*   Updated: 2022/04/28 10:56:03 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**realloc_str(char **ptr, size_t nb_elms)
{
	char	**new_ptr;
	size_t	i;

	new_ptr = malloc(nb_elms * sizeof(char *));
	if (!ptr)
		return (new_ptr);
	if (new_ptr)
	{
		i = 0;
		while (ptr[i] && i < nb_elms)
		{
			new_ptr[i] = ptr[i];
			i++;
		}
	}
	free(ptr);
	return (new_ptr);
}
