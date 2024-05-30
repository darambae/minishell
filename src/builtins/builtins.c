#include "../../minishell.h"

void	run_builtin(char **cmds, int exit_code)
{
	// if (ft_strcmp(cmds[0], "echo"))
	// 	exit_code = ft_echo();
	// else if (ft_strcmp(cmds[0], "cd"))
	// 	ft_cd();
	// else if (ft_strcmp(cmds[0], "pwd"))
	// 	ft_pwd();
	// else if (ft_strcmp(cmds[0], "export"))
	// 	ft_export();
	// else if (ft_strcmp(cmds[0], "unset"))
	// 	ft_unset();
	// else if (ft_strcmp(cmds[0], "env"))
	// 	ft_env();
	// else 
	if (ft_strcmp(cmds[0], "exit") == 0)
		ft_exit(cmds, exit_code);
	//exit(exit_code);
}

