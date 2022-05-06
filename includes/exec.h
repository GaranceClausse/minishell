/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:22:56 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/04 16:08:26 by vkrajcov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include <fcntl.h>
#include "builtins.h"
#include "redirection.h"

typedef struct s_combo {
	t_list	**parser;
	t_env	*env;
	t_lexer	*lexer;
	t_list	*pid_list;
}	t_combo;

char	**token_to_wordlist(t_list *token_list);
int		is_builtin(char *cmd_name);
int		exec_builtin(t_combo *combo, char **wordlist);
char	*get_cmd_name(t_env *env, char *partial_cmd);
int		redir_assign_exec(t_combo *combo, t_cmd *cmd);
int 	exec_commands(t_env *env, t_list *parser, t_lexer *lexer);
int		wait_and_del_pid(t_list *pid_list, int ret);
void	delete_pidlist(t_list *pid_list);
int		add_pid(t_list **pid_list, pid_t *pid);
void	print_pid_list(t_list *pid_list);
void	free_before_exit(t_combo *combo, char **wordlist);

#endif