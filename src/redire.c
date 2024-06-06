#include "../minishell.h"

// static void handle_parent_signal(int sig)
// {
// 	(void)sig;
// 	//printf("^C");
// 	exit_status = 130;
// }

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
	if (rcmd2->token == '{')//if second redire = here_doc
	{
		rcmd->cmd = cmd3;
		rcmd2->cmd = (t_cmd *) rcmd;
		return (rcmd2);//here_doc in first, redir outfile in second
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

	pid = fork1();
	signal(SIGINT, handle_signal_heredoc);
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
		while (line && ft_strcmp(line, rcmd->start_file))
		{
			ft_putstr_fd(ft_strjoin(line, "\n"), rcmd->fd);
			free(line);
			line = readline("> ");
		}
		free(line);
		close(rcmd->fd);
		exit(0);
	}
	//signal(SIGINT, handle_parent_signal);
	while (waitpid(-1, &status, 0) < 0)
	{
		if (exit_status == 130)
		{
			kill(pid, SIGINT);
			waitpid(pid, &status, 0);
			break ;
		}
	}
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		exit_status = 130;
	else
	{
		close(rcmd->fd);
		printf("minishell: warning: here-document delimited by end-of-file\n");
		exit_status = 0;
	}
}
