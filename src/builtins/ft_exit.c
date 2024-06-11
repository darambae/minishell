#include "../../minishell.h"

static bool	only_digit(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(char **cmds)
{
	if (cmds[2])
	{
		ft_error("exit: too many arguments", 1);
		exit(1);
	}
	else if (!cmds[1])
	{
		g_exit_status = 0;
		exit(g_exit_status);
	}
	else if (cmds[1] && only_digit(cmds[1]))
		exit(ft_atoi(cmds[1]) % 256);
	else if (!only_digit(cmds[1]))
	{
		ft_error("exit: numeric argument required", 255);
		exit(1);
	}
}
