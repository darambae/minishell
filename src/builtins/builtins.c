#include "../../minishell.h"

void	run_builtin(char **cmds, int exit_code)
{
	if (ft_strcmp(cmds[0], "echo"))
		ft_echo();
	else if (ft_strcmp(cmds[0], "cd"))
		ft_cd();
	else if (ft_strcmp(cmds[0], "pwd"))
		ft_pwd();
	else if (ft_strcmp(cmds[0], "export"))
		ft_export();
	else if (ft_strcmp(cmds[0], "unset"))
		ft_unset();
	else if (ft_strcmp(cmds[0], "env"))
		ft_env();
	else if (ft_strcmp(cmds[0], "exit"))
		ft_exit(cmds, exit_code);
}

