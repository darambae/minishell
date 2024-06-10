
#include "../minishell.h"

int g_exit_status;

int	ft_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	g_exit_status = EXIT_FAILURE;
	return (0);
}

static void	execute_in_child(t_minishell *g_param)
{
	int			status;
	pid_t		pid;

	pid = fork1();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		run_cmd(g_param->first_cmd, g_param);
		exit(g_exit_status);
	}
	signal(SIGINT, handle_signal_during_execution);
	waitpid(pid, &status, 0);
	handle_exit_status(status);
	setup_parent_signals();
	ft_clean_all(g_param);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	*g_param;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	g_param = init_param(envp);
	setup_parent_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		add_history(line);
		trim_line(line, g_param);
		if (is_executable(g_param->first_cmd, g_param))
		{
			if (is_cd_export_unset(g_param->first_cmd))
				run_cd_export_unset(g_param->first_cmd, g_param);
			else
				execute_in_child(g_param);
		}
		//ft_clean_all(g_param);
	}
	handle_exit(line, g_param);
}
