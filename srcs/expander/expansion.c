#include "expand.h"

char	*extract_var_value(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (ft_strdup(&var[i + 1]));
}

char	*search_var(t_var_list *dst, char *var_name, int j)
{
	int	i;
	char	*ret;
	char	*str;

	i = 0;
	while (dst->list[i])
	{
		str = dst->list[i];
	//	printf("str = %s, var_name = %s, j == %d\n", str, var_name, j);
		if (ft_strncmp(var_name, str, j - 1) == 0)
		{
			ret = extract_var_value(str);
			return (ret);
		}
		i++;
	}
	return ("");
}

int expand_var (t_token *token, t_env *env)
{
	char	*str_expand;
	int		i;
	int		j;

	i = 0;
	while (token->content[i])
	{
		printf("token->content[i] == %c, i == %d \n", token->content[i], i);
		if (token->content[i] == '$')
		{
			j = 1;
			while (ft_isalnum(token->content[j + i]) == 1)
				j++;
			str_expand = search_var(&env->env_var, &token->content[i + 1], j);
			if (str_expand == NULL)
				str_expand = search_var(&env->shell_var, &token->content[i + 1], j);
			printf("ft_substr(token->content, 0, i) == %s, str_expand == %s, &token->content[j + i] = %s\n", ft_substr(token->content, 0, i), str_expand, &token->content[j + i]);
			token->content = ft_strjoin3(ft_substr(token->content, 0, i), str_expand, token->content + (j + i));
			printf("token->content = %s\n", token->content);
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

int	expansion(t_cmd	*cmd, t_env *env)
{
	t_token	*token;
	t_list	*list;

	list = cmd->word_list;
	while (list)
	{
		token = list->content;
		expand_var(token, env);
		list = list->next;
	}
	return (0);
}