#include "../minishell.h"

static void	run_pipe(t_cmd *cmd, int *p, char **envp)
{
    t_pipecmd   *pcmd;
	pid_t		pid1;
	pid_t		pid2;

	pcmd = (t_pipecmd *) cmd;
	if (pipe(p) < 0)
		err_msg("pipe failed");
	g_param->child_pids[g_param->child_count] = fork1();
	if (g_param->child_pids[g_param->child_count] == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		run_cmd(pcmd->left, envp);
		exit(EXIT_SUCCESS);
	}
	g_param->child_count++;
	g_param->child_pids[g_param->child_count] = fork1();
	if (g_param->child_pids[g_param->child_count] == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		run_cmd(pcmd->right, envp);
		exit(EXIT_SUCCESS);
	}
	g_param->child_count++;
	close(p[0]);
	close(p[1]);
	waitpid(g_param->child_pids[g_param->child_count - 2], NULL, 0);
    waitpid(g_param->child_pids[g_param->child_count - 1], NULL, 0);
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
        err_msg("cmd doesn't exist\n");
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
