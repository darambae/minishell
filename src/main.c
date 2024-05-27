
#include "../minishell.h"

t_minishell	*g_param;

static void	init_param(char **envp)
{
	g_param = (t_minishell *)malloc(sizeof(t_minishell));
    if (g_param == NULL) {
        perror("malloc");
        exit(1);
    }
    g_param->child_count = 0;
    g_param->exit_status = 0;
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
	int	fd;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
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
		if (fork1() == 0)
			run_cmd(parse(line), envp);
		for (int i = 0; i < g_param->child_count; i++)
		{
            waitpid(g_param->child_pids[i], &g_param->exit_status, 0); // Wait for each child process to finish
            if (WIFEXITED(g_param->exit_status)) {
                printf("Child %d exited with status: %d\n", g_param->child_pids[i], WEXITSTATUS(g_param->exit_status));
            } else {
                printf("Child %d terminated abnormally\n", g_param->child_pids[i]);
            }
        }
        g_param->child_count = 0; // Reset child count for next command line	
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