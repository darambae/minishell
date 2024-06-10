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
		errno = 1;
		perror("too many arguments");
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
		errno = 1;
		perror("numeric argument required");
		exit(1);
	}
}

