/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:34:26 by gclausse          #+#    #+#             */
/*   Updated: 2022/04/18 10:58:04 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *search(s_env *env, char *var)
{
	int	i;
	int	len;
	char	*haystack;

	i = 0;
	len = ft_strlen(var);
	haystack = env->shell_var->list;
	while (haystack[i])
	{
		if (ft_strncmp(haystack, var, len) == 0)
			return (var);
		i++;
	}
	i = 0;
	haystack = env->env_var->list;
	while (haystack[i])
	{
		if (ft_strncmp(haystack, var, len) == 0)
			return (var);
		i++;
	}
	return (NULL);
}
