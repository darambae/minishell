
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
	g_param->stop = 0;
	return (g_param);
}

int	ft_error(char *msg, t_minishell *g_param)
{
	g_param->stop = 1;
	ft_putstr_fd(msg, 2);
	exit_status = EXIT_FAILURE;
	return (0);
}

// int	line_parsable(t_minishell *g_param)
// {
// 	int	token;
// 	char *tmp;

// 	tmp = g_param->cmd_line;
// 	skip_whitespace(&(g_param->cmd_line), g_param);
// 	if (*(g_param->cmd_line) == '\0')
// 		return (0);
// 	if (*(g_param->cmd_line) == "|" ||
// 		ft_strchr("<>", *(g_param->cmd_line) != NULL ))
// 	{
// 		printf("syntax error near unexpected token '%c'\n", *(++g_param->cmd_line));
// 		return (0);
// 	}
// 	g_param->cmd_line = tmp;
// 	return (1);
// }

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			status;
	pid_t		pid;
	t_minishell	*g_param;
	//int			cur_exit;

	(void)argc;
	(void)argv;
	exit_status = 0;
	g_param = init_param(envp);
	signal(SIGINT, handle_signal_before);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell$ ");
		signal(SIGINT, handle_signal_before);
		//signal(SIGTERM, handle_signal_after);
		if (!line)
			break ;
		else
		{
			add_history(line);
			g_param->cmd_line = ft_strjoin(line, "\0");
			g_param->end_line = g_param->cmd_line + ft_strlen(g_param->cmd_line);
			g_param->start_line = g_param->cmd_line;
			g_param->first_cmd = parse(g_param);
			if (is_executable(g_param->first_cmd, g_param))
			{
				if (is_cd_export_unset(g_param->first_cmd))
					run_cd_export_unset(g_param->first_cmd, g_param);
				else
				{
					pid = fork1();
					if (pid == 0)
					{
						run_cmd(g_param->first_cmd, g_param);
						//exit_status = g_param->exit_status;
						exit(exit_status);
					}
					waitpid(pid, &status, 0);
					handle_exit_status(status);
				}
			}
			waitpid(pid, &status, 0);
			//printf("STATUS: %i\n", status);
			handle_exit_status(status);
		}
		ft_clean_all(g_param);
		//printf("exit_code = %i\n", exit_status);
	}
	if (line == NULL)//why?
	{
		printf("exit\n");
		//printf("%i\n", exit_status);
		exit(0);
	}
	return (0);
}
