/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:24:25 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/08 22:28:10 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

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
		str_expand = search_var(&env->env_var, &input[*i + 1], j);
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

char	*execute_heredoc(t_env *env, char *delimiter, int fd, int expand)
{
	char	*usr_input;
	void	*old_getc;

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
	return (usr_input);
}

int	here_doc(t_env *env, char *delimiter, int fd)
{
	char	*usr_input;
	int		tmp;
	int		expand;

	tmp = g_last_return;
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
/*
int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*delimiter;
	int		fd;

	init_env(&env, 10, envp);
	delimiter = argv[1];
	fd = open(argv[2], O_WRONLY | O_TRUNC, 0677);
	if (argc != 0)
	{
		here_doc(&env, delimiter, fd);
	}
	return (0);
}*/
