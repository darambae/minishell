#include "../../minishell.h"

int    ft_exit(char **cmds)
{
    if (!cmds[1])
    {
        return(g_param->exit_status);
    }
	return (g_param->exit_status);
}
