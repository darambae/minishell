
#include "../minishell.h"

int	exit_status;

char	**make_copy(char **env)
{
	char	**copy;
	int	i;

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
	g_param->env_variables = make_copy(envp);
	g_param->exit_status = 0;
	g_param->cmd_line = NULL;
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
		g_param->cmd_line = ft_strjoin(line, "\0");
		g_param->first_cmd = parse(g_param->cmd_line);
		 if (is_cd_export_unset(g_param->first_cmd))
		 	run_cd_export_unset(g_param->first_cmd);
		else
		{
			pid = fork1();
			if (pid == 0)
			{
				run_cmd(g_param->first_cmd);
				exit(g_param->exit_status);
			}
			waitpid(pid, &status, 0);
			handle_exit_status(status);
		}
		ft_clean_all();
		printf("exit_code = %i\n", g_param->exit_status);
	}
	if (line == NULL)//why?
	{
		printf("exit\n");
		exit(0);
	}
	return (0);
}
