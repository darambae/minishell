
#include "../minishell.h"

void	err_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	//int	p[2];

	(void)argc;
	(void)argv;
	(void)envp;
	while ((line = readline("minishell$ ")) != NULL)
	{
		if (*line)
            add_history(line);
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
		//check if the exact word "exit" was given
		if (ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		line = ft_strjoin(line, "\0");
		if (fork1() == 0)
			run_cmd(parse(line), envp);
		wait(NULL);
	}
	//PSEUDO CODE
	//1. read input
	//2. parse input(make parsing tree)
	//2-1. if input is exit, exit
	//2-2. if input is cd, change directory
	//2-3. if input is env, print environment
	//2-4. if input is setenv, set environment
	//2-5. if input is unsetenv, unset environment
	//2-6. if input is other command, execute command
	//3. execute command
	//3-1. if command is built-in, execute built-in
	//3-2. if command is not built-in, execute command
	//4. free memory
	//5. loop
	return (0);
}