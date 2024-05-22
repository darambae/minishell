
#include "../minishell.h"

void	err_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	//int	pipe[2];

	(void)argc;
	(void)argv;
	while ((line = readline("minishell$ ")) != NULL)
	{
		add_history(line);
		//check if the word "exit" was given ->to make a function
		// printf("%s\n", remove_quotes(line));
		// if (ft_strcmp(line, "exit") == 0)
		// {
		// 	printf("exit\n");
		// 	exit(1);
		// }
		// line = ft_strjoin(line, "\0");
		// if (valid_quote(line))
		// 	printf("Yes, it's valide\n");
		// else
		// 	printf("No, it's not valide\n");

		cmd = parse(line);
		run_cmd(cmd, envp);
	}
	//rl_clear_history();
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