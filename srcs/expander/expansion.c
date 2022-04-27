#include "expand.h"

char	*search_var(t_var_list *dst, char *var_name, int j)
{
	int	i;
	int	index;
	
	i = 0;
	index = search_in_env(dst, var_name, j - 1);
	if (index == -1)
		return (ft_strdup(""));
	else
		return (extract_var_value(dst->list[index]));
}

int	create_new_token(t_token *token, t_env *env, int i, int j)
{
	char	*tmp;
	char	*str_expand;
	char	*str_base;
	int		ret;

	str_expand = search_var(&env->env_var, &token->content[i + 1], j);
	if (str_expand == NULL)
		str_expand = search_var(&env->shell_var, &token->content[i + 1], j);
	str_base = ft_substr(token->content, 0, i);
	tmp = token->content;
	token->content = ft_strjoin3(str_base, str_expand, token->content + (j + i));
	free(tmp);
	ret = ft_strlen(str_expand);
	free(str_base);
	free(str_expand);
	return (ret);
}

void	expand_var(t_token *token, t_env *env)
{
	
	int		quote;
	int		i;
	int		j;

	i = 0;
	quote = 0;
	while (token->content[i])
	{
		if (token->content[i] == '\'')
			quote++;
		if (token->content[i] == '$' && (quote % 2 == 0))
		{
			j = 1;
			while (ft_isalnum(token->content[j + i]) == 1)
				j++;
			i += create_new_token(token, env, i, j);
		}
		else
			i++;
	}
}

void	search_and_expand(t_cmd	*cmd, t_env *env)
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
}