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

int	here_doc(t_redircmd *rcmd)
{
	char	*line;
	pid_t	pid;
	int		exit_status;

	pid = fork1();
	if (pid == 0)
	{
		signal(SIGINT, handle_signal_heredoc);
		rcmd->fd = open(rcmd->start_file, rcmd->mode);
		if (rcmd->fd < 0)
		{
			printf("failed to open %s\n", rcmd->start_file);
			exit(1);
		}
		line = readline("> ");
		while (ft_strcmp(line, rcmd->start_file))
		{
			ft_putstr_fd(ft_strjoin(line, "\n"), rcmd->fd);
			free(line);
			line = readline("> ");
		}
		close(rcmd->fd);
		exit(0);
	}
	// if (errno == ????)
	// 	close(STDIN_FILENO);
	waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	else
		return (130);
}
