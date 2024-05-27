#include "../../minishell.h"

int	check_builtin(char **cmd)
{
	if (ft_strcmp(cmd, "echo"))
		ft_echo(cmd);
	else if (ft_strcmp(cmd, "cd"))
		ft_cd(cmd);
	else if (ft_strcmp(cmd, "pwd"))
		ft_pwd(cmd);
	else if (ft_strcmp(cmd, "export"))
		ft_export(cmd);
	else if (ft_strcmp(cmd, "unset"))
		ft_unset(cmd);
	else if (ft_strcmp(cmd, "env"))
		ft_env(cmd);
	else if (ft_strcmp(cmd, "exit"))
		ft_exit(cmd);
	return (false);
}
