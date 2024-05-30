#include "../../minishell.h"

void    ft_exit(char **cmds)
{
    if (!cmds[1])
    {
        exit(g_param->exit_status);
    }
}
