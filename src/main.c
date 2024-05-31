
#include "../minishell.h"

t_minishell	*g_param;

static void	init_param(char **envp)
{
	g_param = (t_minishell *)malloc(sizeof(t_minishell));
	if (g_param == NULL)
	{
		perror("malloc");
		exit(1);
	}
	g_param->end_line = NULL;
	g_param->end_t = NULL;
	g_param->start_line = NULL;
	g_param->start_t = NULL;
	g_param->env_variables = envp;
	g_param->exit_status = 0;
}

void	err_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;
	pid_t	pid;

	(void)argc;
	(void)argv;
	init_param(envp);
	signal(SIGINT, handle_signal_before);
	signal(SIGQUIT, SIG_IGN);
	while ((line = readline("minishell$ ")) != NULL)
	{
		signal(SIGINT, handle_signal_before);
		signal(SIGQUIT, handle_signal_after);
		if (*line)
			add_history(line);
		line = ft_strjoin(line, "\0");
		pid = fork1();
		if (pid == 0)
			run_cmd(parse(line), g_param);
		waitpid(pid, &status, 0);
		handle_exit_status(status);
		printf("exit_code = %i\n", g_param->exit_status);
		free(line);
	}
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	return (0);
}
