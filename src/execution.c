#include "../minishell.h"

static void	handle_dup(int *p, int in_out, t_pipecmd *pcmd)
{
	if (in_out)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		run_cmd(pcmd->left, g_param);
	}
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		run_cmd(pcmd->right, g_param);
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
	char	    *line;

	rcmd = (t_redircmd *) cmd;
	if (rcmd->token == '{') //here_doc
	{
		line = readline("> ");
		while (ft_strcmp(line, rcmd->start_file))
		{
			ft_putstr_fd(line, rcmd->fd);
			line = ft_strjoin(g_param->cmd_line, ft_strjoin("\n", line));
			rl_replace_line(line, 1);
			add_history(line);
			free(line);
			line = readline("> ");
		}
	}
	close(rcmd->fd);
	if (open(rcmd->start_file, rcmd->mode) < 0)
	{
		printf("failed to open %s\n", rcmd->start_file);
		exit(1);
	}
	if (rcmd->token == '{' || rcmd->token == '[')//redire infile
		dup2(rcmd->fd, STDIN_FILENO);
	else//redire outfile
	{
		rcmd = exchange_cmd_order(rcmd);
		if (rcmd->token == '{')
			run_redire((t_cmd *) rcmd);
		dup2(rcmd->fd, STDOUT_FILENO);
	}
	close(rcmd->fd);
	run_cmd(rcmd->cmd, g_param);
}


t_minishell	*run_cmd(t_cmd *cmd, t_minishell *g_param)
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
			g_param = run_builtin(ecmd->argv, g_param);
		else
			execute_cmd(ecmd->argv);
	}
	else if (cmd->type == PIPE)
		g_param->exit_status = run_pipe(cmd);
	else if (cmd->type == REDIR)
		run_redire(cmd);
	return (g_param);
}
