#include "../minishell.h"

static void handle_dup(int *p, int in_out, t_pipecmd *pcmd)
{
    if (in_out)
    {
        close(p[0]);
        dup2(p[1], STDOUT_FILENO);
        close(p[1]);
        run_cmd(pcmd->left);
    }
    else
    {
        close(p[1]);
        dup2(p[0], STDIN_FILENO);
        close(p[0]);
        run_cmd(pcmd->right);
    } 
}

static int run_pipe(t_cmd *cmd)
{
    t_pipecmd *pcmd = (t_pipecmd *)cmd;
    pid_t   first_pid;
    pid_t   second_pid;
    int     p[2];
    int     exit_status;

    if (pipe(p) < 0)
        err_msg("pipe failed");
    first_pid = fork1();
    if (first_pid == 0)
        handle_dup(p, 1, pcmd);    
    second_pid = fork1();
    if (second_pid == 0)
        handle_dup(p, 0, pcmd);
    close(p[0]);
    close(p[1]);
    waitpid(first_pid, &exit_status, 0);
    waitpid(second_pid, &exit_status, 0);
    if (WIFEXITED(exit_status))
        return (WEXITSTATUS(exit_status));
    else
        return (1);
}

static void	run_redire(t_cmd *cmd)
{
    t_redircmd  *rcmd;
	char	    *line;
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
	run_cmd(rcmd->cmd);
}


int    run_cmd(t_cmd *cmd)
{	
    t_execcmd   *ecmd;
    int         exit_code;

    exit_code = 0;
    if (!cmd)
        err_msg("cdm is empty\n");
    if (cmd->type == EXEC)
    {
        ecmd = (t_execcmd *) cmd;
        if (ecmd->argv[0] == 0)
            exit(0);
        execute_cmd(ecmd->argv);
    }
    else if (cmd->type == PIPE)
		exit_code = run_pipe(cmd);
    else if (cmd->type == REDIR)
		run_redire(cmd);
    exit(exit_code);
}
