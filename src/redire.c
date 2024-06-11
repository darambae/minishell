#include "../minishell.h"

t_redircmd	*exchange_cmd_order(t_redircmd *rcmd)
{
	t_redircmd	*rcmd2;
	t_cmd		*cmd3;

	rcmd2 = NULL;
	cmd3 = NULL;
	if (rcmd->cmd->type != REDIR)
		return (rcmd);
	rcmd2 = (t_redircmd *) rcmd->cmd;
	cmd3 = rcmd2->cmd;
	if (rcmd2->token == '{')
	{
		rcmd->cmd = cmd3;
		rcmd2->cmd = (t_cmd *) rcmd;
		return (rcmd2);
	}
	return (rcmd);
}

void	ft_dup2(t_redircmd *rcmd, int std)
{
	rcmd->fd = open(rcmd->start_file, rcmd->mode);
	if (rcmd->fd < 0)
	{
		printf("failed to open %s\n", rcmd->start_file);
		exit(1);
	}
	if (dup2(rcmd->fd, std) < 0)
	{
		close(rcmd->fd);
		printf("failed to dup");
		exit(1);
	}
	close(rcmd->fd);
}

void	here_doc(t_redircmd *rcmd)
{
	char	*line;
	pid_t	pid;
	int		status;

	// if (param->fd_out)
	// 	dup2(param->save_out, STDOUT_FILENO);
	pid = fork1();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		rcmd->fd = open(rcmd->start_file, rcmd->mode);
		if (rcmd->fd < 0)
		{
			printf("failed to open %s\n", rcmd->start_file);
			exit(EXIT_FAILURE);
		}
		line = readline("> ");
		while (ft_strcmp(line, rcmd->start_file))
		{
			ft_putstr_fd(ft_strjoin(line, "\n"), rcmd->fd);
			free(line);
			line = readline("> ");
		}
		free(line);
		close(rcmd->fd);
		exit(g_exit_status);
	}
	signal(SIGINT, handle_signal_heredoc);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_exit_status = 130;
		exit(130);
	}
	else
	{
		close(rcmd->fd);
		printf("minishell: warning: here-document delimited by end-of-file\n");
		g_exit_status = 0;
	}
}
