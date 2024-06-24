#include "../../minishell.h"

bool	is_cd_export_unset(t_cmd *cmd)
{
	t_execcmd	*res;

	res = (t_execcmd *)cmd;
	if (!res->argv[0])
		return (false);
	if (!ft_strcmp(res->argv[0], "cd") || !ft_strcmp(res->argv[0], "export") \
		|| !ft_strcmp(res->argv[0], "unset"))
		return (true);
	return (false);
}

void	run_cd_export_unset(t_cmd *cmd, t_minishell *param)
{
	t_execcmd	*res;

	res = (t_execcmd *)cmd;
	if (!ft_strcmp(res->argv[0], "cd"))
		ft_cd(res, param);
	else if (!ft_strcmp(res->argv[0], "export"))
		ft_export(res, param);
	else if (!ft_strcmp(res->argv[0], "unset"))
		ft_unset(res, param);
}

bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") \
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit") \
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") \
		|| !ft_strcmp(cmd, "cd"))
		return (true);
	return (false);
}

void	run_builtin(char **argv, t_minishell *param)
{
	if (!ft_strcmp(argv[0], "echo"))
		g_exit_status = ft_echo(argv);
	else if (!ft_strcmp(argv[0], "pwd"))
		g_exit_status = ft_pwd();
	else if (!ft_strcmp(argv[0], "env"))
		g_exit_status = ft_env(argv, param);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv);
	else if (!ft_strcmp(argv[0], "export") || !ft_strcmp(argv[0], "unset") \
		|| !ft_strcmp(argv[0], "cd"))
		g_exit_status = 1;
	exit(g_exit_status);
}
