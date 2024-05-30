#include "../../minishell.h"

void    ft_exit(char **cmds, int exit_code)
{
    if (!cmds[1])
    {
        exit(exit_code);
    }
}