#include "../../minishell.h"

bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || \
		!ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

t_minishell	*run_builtin(char **argv, t_minishell *g_param)
{
	if (!ft_strcmp(argv[0], "echo"))
		g_param->exit_status = ft_echo(argv);
	else if (!ft_strcmp(argv[0], "cd"))
	{
		ft_cd(argv, g_param);
		return (g_param);
	}
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

