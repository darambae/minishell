#include "../minishell.h"

int	g_exit_status;

static void	execute_in_child(t_minishell *param)
{
	int			status;
	pid_t		pid;

	pid = fork1();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		run_cmd(param->first_cmd, param);
		exit(g_exit_status);
	}
	signal(SIGINT, handle_signal_during_execution);
	signal(SIGQUIT, handle_signal_during_execution);
	waitpid(pid, &status, 0);
	handle_exit_status(status);
	setup_parent_signals();
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	*param;

	(void)argc;
	(void)argv;
	param = NULL;
	param = init_param(envp);
	setup_parent_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line || ft_strncmp(line, "exit", 4) == 0)
			break ;
		add_history(line);
		trim_line(line, param);
		if (is_executable(param->first_cmd, param))
		{
			if (is_cd_export_unset(param->first_cmd))
				run_cd_export_unset(param->first_cmd, param);
			else
				execute_in_child(param);
		}
		ft_clean_all(line, param);
	}
	handle_exit(line, param);
}
