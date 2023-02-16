#include <unistd.h>

int main(void)
{
	int	i = 0;
	int	fds[2];

	while (i < 2)
	{
		if (i == 1)
		{
			pipe(fds);
			write(fds[1], "kjgsk\n", 6);
		}
		i++;
	}
	printf("I'm Here\n");
	return (0);
}


/*

void    apply_priorities(t_proc **proc, int *level)
{
        if (g_data.exit_status && (*proc)->separator == AND_TOKEN)
        {
                *level = (*proc)->level;
                while (priority_condition(*proc, *level, AND_TOKEN))
                        *proc = (*proc)->next;
        }
        else if (g_data.exit_status == 0 && (*proc)->separator == OR_TOKEN)
        {
                *level = (*proc)->level;
                while (priority_condition(*proc, *level, OR_TOKEN))
                {
                        if ((*proc)->separator == AND_TOKEN)
                                *level = (*proc)->level;
                        *proc = (*proc)->next;
                }
        }
}


typedef struct s_inspector
{
        t_proc  *current;
        int             _pipe[2];
        int             prev_pipe[2];
        int             i;
        int             level;
}       t_inspector;

void    inspector(void)
{
        t_inspector     s;

        look_for_cmd_not_found();
        s.i = -1;
        s.current = g_data.head;
        while (s.current)
        {
                check_if_dots(&s.current);
                check_if_directory(&s.current);
                init_inspector_and_exec(s.current, s._pipe, s.prev_pipe, s.i);
                apply_priorities(&s.current, &s.level);
                s.i++;
                if (s.current->separator != PIPE_TOKEN)
                        s.i = -1;
                s.current = s.current->next;
        }
        close(s._pipe[0]);
        close(s._pipe[1]);
        close(s.prev_pipe[0]);
        close(s.prev_pipe[1]);
        close_heredocs();
}


int     priority_condition(t_proc *proc, int level, int token)
{
        if (token == AND_TOKEN)
                return (proc && (proc->separator == AND_TOKEN
                                || proc->separator == PIPE_TOKEN) && proc->level >= level);
        else if (token == OR_TOKEN)
                return (proc && ((proc->separator == OR_TOKEN
                                        || proc->separator == PIPE_TOKEN)
                                || (proc->separator == AND_TOKEN
                                        && proc->level > level)) && proc->level >= level);
        return (EXIT_SUCCESS);
}

*/