
#include "../minishell.h"

int exit_status;

char	**make_copy(char **env)
{
	char	**copy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (i == 0)
		return (NULL);
	copy = malloc((i + 1) * sizeof(char *));
	if (!copy)

		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static t_minishell	*init_param(char **envp)
{
	t_minishell	*g_param;

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
	g_param->env_variables = make_copy(envp);
	g_param->exit_status = 0;
	g_param->cmd_line = NULL;
	g_param->save_out = dup(STDOUT_FILENO);
	g_param->save_in = dup(STDIN_FILENO);
	return (g_param);
}

int	ft_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit_status = EXIT_FAILURE;
	return (0);
}

void	trim_line(char *line, t_minishell *g_param)
{
	g_param->cmd_line = ft_strjoin(line, "\0");
	g_param->end_line = g_param->cmd_line + ft_strlen(g_param->cmd_line);
	g_param->start_line = g_param->cmd_line;
	g_param->first_cmd = parse(g_param);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			status;
	pid_t		pid;
	t_minishell	*g_param;

	(void)argc;
	(void)argv;
	exit_status = 0;
	g_param = init_param(envp);
	setup_parent_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		trim_line(line, g_param);
		if (is_executable(g_param->first_cmd, g_param))
		{
			if (is_cd_export_unset(g_param->first_cmd))
				run_cd_export_unset(g_param->first_cmd, g_param);
			else
			{
				pid = fork1();
				if (pid == 0)
				{
					signal(SIGINT, SIG_DFL);
					run_cmd(g_param->first_cmd, g_param);
					exit(exit_status);
				}
				signal(SIGINT, handle_signal_during_execution);
				waitpid(pid, &status, 0);
				handle_exit_status(status);
				setup_parent_signals();
			}
		}
		ft_clean_all(g_param);
	}
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	return (0);
}
