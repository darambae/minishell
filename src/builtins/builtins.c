#include "../../minishell.h"

void	is_cd_export_unset(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(cmd);
}

bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") \
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

t_minishell	*run_builtin(char **argv, t_minishell *g_param)
{
	if (!ft_strcmp(argv[0], "echo"))
		g_param->exit_status = ft_echo(argv);
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

