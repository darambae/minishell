#include "../minishell.h"

static void	handle_dup(int *p, int in_out, t_pipecmd *pcmd)
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

static int	run_pipe(t_cmd *cmd)
{
	t_pipecmd	*pcmd;
	pid_t		first_pid;
	pid_t		second_pid;
	int			p[2];
	int			exit_status;

	pcmd = (t_pipecmd *)cmd;
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
		return (130);
}

static void	run_redire(t_cmd *cmd)
{
	t_redircmd  *rcmd;

	rcmd = (t_redircmd *) cmd;
	close(rcmd->fd);
	if (rcmd->token == '{') //here_doc
		here_doc(rcmd);
	if (rcmd->token == '{' || rcmd->token == '[')//redire infile
		ft_dup2(rcmd, STDIN_FILENO);
	else//redire outfile
	{
		rcmd = exchange_cmd_order(rcmd);
		if (rcmd->token == '{')
			run_redire((t_cmd *) rcmd);
		ft_dup2(rcmd, STDOUT_FILENO);
	}
	run_cmd(rcmd->cmd);
}


t_minishell	*run_cmd(t_cmd *cmd)
{
	t_execcmd	*ecmd;

	if (!cmd)
		err_msg("cdm is empty\n");
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *) cmd;
		if (ecmd->argv[0] == 0)
			exit(0);
		if (is_builtin(ecmd->argv[0]) == true)
			g_param = run_builtin(ecmd->argv);
		else
			execute_cmd(ecmd->argv);
	}
	else if (cmd->type == PIPE)
		g_param->exit_status = run_pipe(cmd);
	else if (cmd->type == REDIR)
		run_redire(cmd);
	return (g_param);
}
