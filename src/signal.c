#include "../minishell.h"


void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
		g_param->exit_status = WEXITSTATUS(status);
	else
	{
		g_param->exit_status = 43;
		printf("minishell: warning: here-document delimited by end-of-file\n");
		errno = 1;
	}
}

void	handle_signal_before(int sig)
{
	(void)sig;
	printf("\n");
	g_param->exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal_after(int sig)
{
	if (sig == SIGINT)
	{
		g_param->exit_status = 130;
		printf("^C");
	}
	else if (sig == SIGQUIT)
	{
		g_param->exit_status = 0;
		printf("exit\n");
	}
}