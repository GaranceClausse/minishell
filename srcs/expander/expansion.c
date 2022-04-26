#include "expand.h"

char	*extract_var_value(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i + 1])
		return (ft_strdup(&var[i + 1]));
	else
		return ("");
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
		if (ft_strncmp(var_name, str, j) == 0)
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
	char	*str;
	char	*str_expand;
	int		i;
	int		j;

	i = 0;
	while(token->content[i])
	{
		if(token->content[i] == '$')
		{
			j = 1;
			while (ft_isalnum(token->content[j]) == 1)
				j++;
			str_expand = search_var(&env->env_var, &token->content[i + 1], j);
			if (str_expand == NULL)
				str_expand = search_var(&env->shell_var, &token->content[i + 1], j);
			token->content = ft_strjoin3(ft_substr(token->content, 0, i), str_expand, &token->content[j]);
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

	while (cmd->word_list)
	{
		token = cmd->word_list->content;
		expand_var(token, env);
		cmd->word_list = cmd->word_list->next;
	}
	return (0);
}