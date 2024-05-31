#include "../../minishell.h"

void	run_builtin(char **argv, t_minishell *g_param)
{
	if (!ft_strcmp(argv[0], "echo"))
		g_param->exit_status = ft_echo(argv);
	else if (!ft_strcmp(argv[0], "cd"))
		ft_cd(argv, g_param);
	/*else if (!ft_strcmp(argv[0], "export"))
		ft_export();
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset();*/
	else if (!ft_strcmp(argv[0], "pwd"))
		g_param->exit_status = ft_pwd();
	else if (!ft_strcmp(argv[0], "env"))
		g_param->exit_status = ft_env(argv);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv, g_param->exit_status);
	exit(g_param->exit_status);
}

