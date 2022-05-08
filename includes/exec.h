/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deacllock <deacllock@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:22:56 by gclausse          #+#    #+#             */
/*   Updated: 2022/05/08 22:22:59 by deacllock        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <fcntl.h>
# include "builtins.h"
# include "redirection.h"

typedef struct s_combo {
	t_list	**parser;
	t_env	*env;
	t_lexer	*lexer;
	t_list	*pid_list;
}	t_combo;

char	**token_to_wordlist(t_list *token_list);
int		is_builtin(char *cmd_name);
int		handle_builtins(t_combo *combo, t_cmd *cmd, char **wordlist);
int		get_cmd_name(t_env *env, char **partial_cmd);
int		redir_assign_exec(t_combo *combo, t_cmd *cmd);
int		exec_commands(t_env *env, t_list *parser, t_lexer *lexer);
char	**get_wordlist(t_combo *combo, t_cmd *cmd);
int		wait_all_pids(t_list *parser, int ret);
void	free_before_exit(t_combo *combo, char **wordlist);
int		fork_and_exec(t_combo *combo, t_cmd *cmd);
int		shall_i_fork(t_cmd	*cmd);
int		exec_or_assign_only(t_combo *combo, t_cmd *cmd);

#endif