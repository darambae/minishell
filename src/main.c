
#include "../minishell.h"

void	err_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(0);
}

int	main(int argc, char **argv)
{
	char	*line;
	t_cmd	*cmd;
	//int	pipe[2];

	(void)argc;
	(void)argv;
	while ((line = readline("minishell$ ")) != NULL)
	{
		add_history(line);
		line = ft_strjoin(line, "\0");
		cmd = parse(line);
		if (valid_quote(line))
			printf("Yes, it's valide\n");
		else
			printf("No, it's not valide\n");
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