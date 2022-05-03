/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:24:25 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/03 17:24:18 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "env.h"
#include "expand.h"

extern int	g_last_return;

char	*remove_quotes_heredoc(char *delimiter)
{
	
	int		i;
	char	*cpy;

	i = 0;
	cpy = malloc(sizeof(char) * (ft_strlen(delimiter) + 1));
	if (!cpy)
		return (NULL);
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			i++;
		else
			cpy[i] = delimiter[i];
		i++;
	}
	free(delimiter);
	return (cpy);
}

char	*expand_heredoc(char *input, t_env *env)
{
	int		i;
	int		j;
	char	*str_expand;
	char	*str_base;
	char	*tmp;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			j = 1;
			if (input[i + 1] && input[i + 1] == '?')
			{
				str_expand = ft_itoa(g_last_return);
				j += 1;
			}
			else
			{				
				while (input[j + i]
				&& (ft_isalnum(input[j + i]) == 0
					|| ft_isunderscore(input[j + i]) == 0))
					j++;
				str_expand = search_var(&env->env_var, &input[i + 1], j);
			}
			str_base = ft_substr(input, 0, i);
			tmp = input;
			input = ft_strjoin3(str_base, str_expand, input + (j + i));
			free(tmp);
			i += ft_strlen(str_expand);
			free(str_base);
			free(str_expand);
		}
		else
			i++;
	}
	return (input);
}

int	here_doc(t_env *env, char *delimiter, int fd)
{
	char	*usr_input;
	void	*old_getc;
	int		tmp;
	int		expand;

	tmp = g_last_return;
	g_last_return = 0;
	expand = 1;
	if (fd == -1)
		return (1);
	if (ft_strchr(delimiter, '\'') != NULL || ft_strchr(delimiter, '\"') != NULL)
	{
		delimiter = remove_quotes_heredoc(delimiter);
		expand = 0;
	}
	signal(SIGINT, sigint_handler);
	old_getc = rl_getc_function;
	rl_getc_function = getc;
	write(1, "here_doc > ", 12);
	usr_input = readline(NULL);
	while (g_last_return != 130 && usr_input
		&& ft_strcmp(usr_input, delimiter) != 0)
	{
		if (expand == 1)
			usr_input = expand_heredoc(usr_input, env);
		write(1, "here_doc > ", 12);
		write(fd, usr_input, ft_strlen(usr_input));
		write(fd, "\n", 1);
		free(usr_input);
		usr_input = readline(NULL);
	}
	free(usr_input);
	rl_getc_function = old_getc;
	if (g_last_return)
		return (1);
	g_last_return = tmp;
	if (!usr_input)
	{
		printf("unexpected end of file (wanted '%s')\n", delimiter);
		return (1);
	}
	return (0);
}