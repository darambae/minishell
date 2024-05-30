
#include "../minishell.h"

t_minishell	*g_param;

static void	init_param(char **envp)
{
	g_param = (t_minishell *)malloc(sizeof(t_minishell));
    if (g_param == NULL) {
        perror("malloc");
        exit(1);
    }
	g_param->end_line = NULL;
	g_param->end_t = NULL;
	g_param->start_line = NULL;
	g_param->start_t = NULL;
	g_param->env_variables = envp;
}

void	err_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		fd;
	int		status;
	pid_t	pid;
	int		exit_code;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGQUIT, handle_signal);
	init_param(envp);

	while((fd = open("console", O_RDWR)) >= 0)
	{
		if(fd >= 3)
		{
			close(fd);
			break;
		}
  	}
	while ((line = readline("minishell$ ")) != NULL)
	{
		if (*line)
            add_history(line);
		//check if the exact word "exit" was given
		if (ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		line = ft_strjoin(line, "\0");
		pid = fork1();
		if (pid == 0)
			run_cmd(parse(line));
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
        	exit_code = WEXITSTATUS(status);
		printf("Exit status of the last child process is %i\n", exit_code);
		free(line);
	}
	if (line == NULL)
	{
        printf("exit\n");
        exit(0);
	}
	return (0);
}
//     // Simulate a condition where we replace the line and clear history
    //     if (strcmp(line, "replace") == 0) {
    //         rl_replace_line("This is the replaced line", 1);
	// 		rl_on_new_line();
    //         rl_redisplay();
    //     } else if (strcmp(line, "clear") == 0) {
    //         rl_clear_history();
    //         printf("\nHistory cleared.\n");
    //         rl_on_new_line();
    //         rl_redisplay();
    //     }
    //     // Continue with your shell logic...
    //     printf("You entered: %s\n", line);

    //     // Free the allocated line
    //     free(line);
    // }
