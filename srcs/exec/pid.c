#include "exec.h"
#include <sys/wait.h>
#include <sys/types.h>

extern int g_last_return;

void	wait_all_pids(t_list *pid_list)
{
	pid_t	*pid;
	int		wstatus;

	wstatus = 1;
	while (pid_list)
	{
		pid = (pid_t *)pid_list->content;
		//checker si ca intercepte les signaux
		if (*pid != -1)
			waitpid(*pid, &wstatus, 0);
		//while (WIFSTOPPED(wstatus) || WIFCONTINUED(wstatus))
		//	waitpid(*cur, &wstatus, WUNTRACED | WCONTINUED);
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
	{
		free(pid);
		return (1);
	}
	ft_lstadd_back(pid_list, new);
	return (0);
}

int	wait_and_del_pid(t_list *pid_list, int ret)
{
	wait_all_pids(pid_list);
	ft_lstclear(&pid_list, free);
	return (ret);
}