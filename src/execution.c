#include "../minishell.h"

void    run_cmd(t_cmd *cmd)
{
    int fd[2];

    t_execcmd   *ecmd;
    t_pipecmd   *pcmd;
    t_redircmd  *rcmd;

    if (!cmd)
        err_msg("cdm doesn't exist");
    if (cmd->type == EXEC)
    {
        ecmd = (t_execcmd *) cmd;
    }
    else if (cmd->type == PIPE)
    {
        pcmd = (t_pipecmd *) cmd;
    }
    else if (cmd->type == REDIR)
    {
        rcmd = (t_redircmd *) cmd;
    }
    exit(0);
}