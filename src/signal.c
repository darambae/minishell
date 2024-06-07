#include "../minishell.h"

void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		g_exit_status = 130;
	else
		g_exit_status = EXIT_FAILURE;
}

void	handle_signal_during_execution(int sig)
{
	(void)sig;
	g_exit_status = 130;
	printf("\n");
	rl_redisplay();
}

void	setup_parent_signals(void)
{
	signal(SIGINT, handle_signal_before);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signal_before(int sig)
{
	(void)sig;
	printf("\n");
	g_exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal_heredoc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	printf("^C\n");
	exit(130);
}
