#include "../minishell.h"

// void	run_after_hd(t_cmd *cmd)
// {
// 	t_redircmd	*rcmd;
// 	t_pipecmd	*pcmd;

// 	if (cmd->type == PIPE)
// 	{
// 		pcmd = (t_pipecmd *) cmd;
// 		run_after_hd(pcmd->left);
// 		run_after_hd(pcmd->right);
// 	}
// 	else if (cmd->type == REDIR)
// 	{
// 		rcmd = (t_redircmd *) cmd;
// 		if (rcmd->token == '{' && rcmd->here_doc == 0)
// 		{
// 			rcmd->here_doc = 1;
// 			run_cmd((t_cmd *) rcmd);
// 		}
// 		else
// 			run_after_hd(rcmd->cmd);
// 	}
// 	else if (cmd->type == EXEC)
// 		return;
// }


void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		printf("exit_code = %i\n", exit_status);
	}
	else
	{
		exit_status = 43;
		printf("minishell: warning: here-document delimited by end-of-file\n");
		errno = 1;
	}
}

void	handle_signal_before(int sig)
{
	(void)sig;
	printf("\n");
	exit_status = 200;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal_after(int sig)
{
	if (sig == SIGINT)
	{
		exit_status = 220;
		//printf("^C");
	}
	if (sig == SIGTERM)
	{
		exit_status = 137;
		printf("%i\n", exit_status);
		printf("exit\n");
	}
}

void	handle_signal_heredoc(pid_t pid)
{
	kill(pid, SIGINT);
	//(void)pid;
	//close(STDIN_FILENO);
	exit_status = 130;
	printf("^C\n");
	exit(exit_status);
}