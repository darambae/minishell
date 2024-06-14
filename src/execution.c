#include "../minishell.h"

static void	handle_right(int *p, t_pipecmd *pcmd, t_minishell *param)
{
	t_redircmd	*rcmd;

	if (pcmd->right->type == REDIR)
	{
		rcmd = (t_redircmd *) pcmd->right;
		rcmd = exchange_cmd_order(rcmd);
		if (rcmd->token == '{')
		{
			dup2(param->save_in, STDIN_FILENO);
			here_doc(rcmd);
			ft_dup2(rcmd, STDIN_FILENO);
			pcmd->right = rcmd->cmd;
		}
	}
	else
		dup2(p[0], STDIN_FILENO);
	close(p[1]);
	close(p[0]);
	run_cmd(pcmd->right, param);
}

static void	handle_dup(int *p, int left, t_pipecmd *pcmd, t_minishell *param)
{
	t_redircmd	*rcmd;

	if (left)
	{
		close(p[0]);
		if (pcmd->left->type == REDIR)
		{
			rcmd = (t_redircmd *) pcmd->left;
			rcmd = exchange_cmd_order(rcmd);
			if (rcmd->token == '{')
			{
				dup2(param->save_in, STDIN_FILENO);
				here_doc(rcmd);
				ft_dup2(rcmd, STDIN_FILENO);
				pcmd->left = rcmd->cmd;
			}
		}
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		run_cmd(pcmd->left, param);
	}
	else
		handle_right(p, pcmd, param);
}

static int	run_pipe(t_cmd *cmd, t_minishell *g_param)
{
	t_pipecmd	*pcmd;
	pid_t		first_pid;
	pid_t		second_pid;
	int			p[2];
	int			g_exit_status;

	pcmd = (t_pipecmd *)cmd;
	if (pipe(p) < 0)
		ft_error("pipe error", 1);
	first_pid = fork1();
	if (first_pid == 0)
		handle_dup(p, 1, pcmd, g_param);
	waitpid(first_pid, &g_exit_status, 0);
	second_pid = fork1();
	if (second_pid == 0)
		handle_dup(p, 0, pcmd, g_param);
	close(p[0]);
	close(p[1]);
	waitpid(second_pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		return (WEXITSTATUS(g_exit_status));
	else
		return (1);
}

static void	run_redire(t_cmd *cmd, t_minishell *g_param)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	close(rcmd->fd);
	if (rcmd->token == '{')
		here_doc(rcmd);
	if (rcmd->token == '{' || rcmd->token == '[')
		ft_dup2(rcmd, STDIN_FILENO);
	else
	{
		rcmd = exchange_cmd_order(rcmd);
		if (rcmd->token == '{')
			run_redire((t_cmd *)rcmd, g_param);
		ft_dup2(rcmd, STDOUT_FILENO);
	}
	run_cmd(rcmd->cmd, g_param);
}

void	run_cmd(t_cmd *cmd, t_minishell *g_param)
{
	t_execcmd	*ecmd;

	if (!cmd)
		perror("cmd is empty");
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			exit(0);
		if (is_builtin(ecmd->argv[0]) == true)
			run_builtin(ecmd->argv, g_param);
		else
			execute_cmd(ecmd->argv, g_param);
	}
	else if (cmd->type == PIPE)
		g_exit_status = run_pipe(cmd, g_param);
	else if (cmd->type == REDIR)
		run_redire(cmd, g_param);
}
