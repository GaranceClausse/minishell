#include "exec.h"
#include <sys/wait.h>
#include <sys/types.h>

int	wait_all_pids(t_list *parser)
{
	t_cmd	*cmd;
	int		wstatus;

	wstatus = 1;
	while (parser)
	{
		cmd = (t_cmd *)parser->content;
		//checker si ca intercepte les signaux
		if (cmd->pid != -1)
			waitpid(cmd->pid, &wstatus, 0);
		//while (WIFSTOPPED(wstatus) || WIFCONTINUED(wstatus))
		//	waitpid(*cur, &wstatus, WUNTRACED | WCONTINUED);
		parser = parser->next;
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (EXIT_FAILURE);
}