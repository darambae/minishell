#include "../../minishell.h"

bool	is_cd_export_unset(t_cmd *cmd)
{
	t_execcmd	*res;

	res = (t_execcmd *)cmd;

	if (!ft_strcmp(res->argv[0], "cd") || !ft_strcmp(res->argv[0], "export") \
		|| !ft_strcmp(res->argv[0], "unset"))
		return (true);
	return (false);
}

void	run_cd_export_unset(t_cmd *cmd, t_minishell *g_param)
{
	t_execcmd	*res;

	res = (t_execcmd *)cmd;
	if (!ft_strcmp(res->argv[0], "cd"))
		ft_cd(res, g_param);
	else if (!ft_strcmp(res->argv[0], "export"))
		ft_export(res, g_param);
	else if (!ft_strcmp(res->argv[0], "unset"))
		ft_unset(res, g_param);
}

bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") \
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

void	run_builtin(char **argv, t_minishell *g_param)
{
	if (!ft_strcmp(argv[0], "echo"))
		g_param->exit_status = ft_echo(argv);
	else if (!ft_strcmp(argv[0], "pwd"))
		g_param->exit_status = ft_pwd();
	else if (!ft_strcmp(argv[0], "env"))
		g_param->exit_status = ft_env(argv, g_param);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv);
	exit(g_param->exit_status);
}

