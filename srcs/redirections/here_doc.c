/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:24:25 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/12 20:24:19 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

char	*remove_quotes_heredoc(char *delimiter)
{
	int		i;
	int		j;
	char	*cpy;

	i = 0;
	j = 0;
	cpy = malloc(sizeof(char) * (ft_strlen(delimiter) + 1));
	if (!cpy)
		return (NULL);
	while (delimiter[i])
	{
		if (!(delimiter[i] == '\'' || delimiter[i] == '"'))
		{
			cpy[j] = delimiter[i];
			j++;
		}
		i++;
	}
	cpy[j] = '\0';
	return (cpy);
}

char	*create_expanded_string(t_env *env, char *input, int *i, int j)
{
	char	*str_expand;
	char	*str_base;
	char	*tmp;

	if (input[*i + 1] && input[*i + 1] == '?')
	{
		str_expand = ft_itoa(g_last_return);
		j += 1;
	}
	else
	{				
		while (input[j + *i]
			&& (ft_isalnum(input[j + *i]) == 0
				|| ft_isunderscore(input[j + *i]) == 0))
			j++;
		str_expand = search_var(env, &input[*i + 1], j);
	}
	str_base = ft_substr(input, 0, *i);
	tmp = input;
	input = ft_strjoin3(str_base, str_expand, input + (j + *i));
	free(tmp);
	i += ft_strlen(str_expand);
	free(str_base);
	free(str_expand);
	return (input);
}

char	*expand_heredoc(char *input, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (input[i])
	{
		if (input[i] == '$')
			input = create_expanded_string(env, input, &i, j);
		else
			i++;
	}
	return (input);
}

static char	*execute_heredoc(t_env *env, char *delimiter, int fd, int expand)
{
	char	*usr_input;
	void	*old_getc;

	old_getc = rl_getc_function;
	rl_getc_function = getc;
	signal(SIGINT, sigint_handler_multiline);
	usr_input = readline("here_doc > ");
	signal(SIGINT, SIG_IGN);
	while (g_last_return != 130 && usr_input
		&& ft_strcmp(usr_input, delimiter) != 0)
	{
		if (expand == 1)
			usr_input = expand_heredoc(usr_input, env);
		ft_putstr_fd(usr_input, fd);
		ft_putstr_fd("\n", fd);
		free(usr_input);
		signal(SIGINT, sigint_handler);
		usr_input = readline("here_doc > ");
		signal(SIGINT, SIG_IGN);
	}
	rl_getc_function = old_getc;
	return (usr_input);
}

int	here_doc(t_env *env, char *delimiter, int fd)
{
	int		expand;
	char	*usr_input;

	g_last_return = 0;
	expand = 1;
	if (fd == -1)
		return (1);
	if (ft_strchr(delimiter, '\'') != NULL
		|| ft_strchr(delimiter, '\"') != NULL)
	{
		delimiter = remove_quotes_heredoc(delimiter);
		expand = 0;
	}
	usr_input = execute_heredoc(env, delimiter, fd, expand);
	if (!usr_input && g_last_return != 130)
	{
		ft_putstr_fd("\nunexpected end of file (wanted '", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
	}
	if (expand == 0)
		free(delimiter);
	free(usr_input);
	return (g_last_return);
}
