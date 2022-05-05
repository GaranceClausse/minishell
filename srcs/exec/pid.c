#include "exec.h"
#include <sys/wait.h>
#include <sys/types.h>

extern int g_last_return;

void	wait_all_pids(t_list *pid_list)
{
	int	*cur;
	int	wstatus;

	wstatus = 1;
	while (pid_list)
	{
		cur = (int *)pid_list->content;
		//checker si ca intercepte les signaux
		//while (WIFSTOPPED(wstatus) || WIFCONTINUED(wstatus))
		waitpid(*cur, &wstatus, 0);
		pid_list = pid_list->next;
	}
	if (WIFEXITED(wstatus))
		g_last_return = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		g_last_return = (128 + WTERMSIG(wstatus));
}

int	add_pid(t_list **pid_list, pid_t *pid)
{
	t_list	*new;

	new = ft_lstnew((void *)pid);
	if (!new)
		return (1);
	ft_lstadd_back(pid_list, new);
	return (0);
}

void	delete_pidlist(t_list *pid_list)
{
	t_list	*cur;
	t_list	*next;

	cur = pid_list;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

int	wait_and_del_pid(t_list *pid_list, int ret)
{
	wait_all_pids(pid_list);
	delete_pidlist(pid_list);
	return (ret);
}