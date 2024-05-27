#include "../minishell.h"

static void	run_pipe(t_cmd *cmd, int *p, char **envp)
{
    t_pipecmd   *pcmd;

	pcmd = (t_pipecmd *) cmd;
	if (pipe(p) < 0)
		err_msg("pipe failed");
	if (fork1() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		run_cmd(pcmd->left, envp);
	}
	if (fork1() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		run_cmd(pcmd->right, envp);
	}
	close(p[0]);
	close(p[1]);
	wait(NULL);
	wait(NULL);
}

static void	run_redire(t_cmd *cmd, char **envp)
{
    t_redircmd  *rcmd;
	char	*line;
	//int		j;

	rcmd = (t_redircmd *) cmd;
	if (rcmd->token == '{') //here_doc
	{
		line = readline("> ");
		//j = 0;
		while (ft_strcmp(line, rcmd->start_file))
		{
			//rcmd->here_doc[j++] = ft_strdup(line);
			line = readline("> ");
			add_history(line);
		}
	}
	else
	{
		close(rcmd->fd);
		if (open(rcmd->start_file, rcmd->mode) < 0)
		{
			printf("failed to open %s\n", rcmd->start_file);
			exit(1);
		}
	}
	run_cmd(rcmd->cmd, envp);
}

void    run_cmd(t_cmd *cmd, char **envp)
{
    int p[2];
	
    t_execcmd   *ecmd;

    if (!cmd)
        err_msg("cdm doesn't exist\n");
    if (cmd->type == EXEC)
    {
        ecmd = (t_execcmd *) cmd;
        if (ecmd->argv[0] == 0)
            exit(0);
        execute_cmd(ecmd->argv, envp);
    }
    else if (cmd->type == PIPE)
		run_pipe(cmd, p, envp);
    else if (cmd->type == REDIR)
		run_redire(cmd, envp);
    exit(0);
}
