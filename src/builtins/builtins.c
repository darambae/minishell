#include "../../minishell.h"

void	run_builtin(char **argv, int exit_code)
{
	if (!ft_strcmp(argv[0], "echo"))
		g_param->exit_status = ft_echo(argv);
	/*else if (ft_strcmp(argv[0], "cd"))
		ft_cd();
	else if (ft_strcmp(argv[0], "export"))
		ft_export();
	else if (ft_strcmp(argv[0], "unset"))
		ft_unset();*/
	else if (!ft_strcmp(argv[0], "pwd"))
		g_param->exit_status = ft_pwd();
	else if (!ft_strcmp(argv[0], "env"))
		g_param->exit_status = ft_env(argv);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv, exit_code);
	exit(g_param->exit_status);
}

