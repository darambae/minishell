#include "../../minishell.h"

// static int	grep_only_num(const char *nptr)
// {
// 	int	sign;
// 	int	res;
// 	int	i;

// 	sign = 1;
// 	res = 0;
// 	i = 0;
// 	if (nptr[i] == '-' || nptr[i] == '+')
// 	{
// 		if (nptr[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	if (nptr[i] == '"')
// 	{
// 		while (ft_isdigit(nptr[++i]))
// 			res = res * 10 + (nptr[i] - 48);
// 		if (nptr[i] == '"')
// 			return (res * sign);
// 		else
// 			return (ft_error("exit syntax error", errno));
// 	}
// 	while (ft_isdigit(nptr[i]))
// 		res = res * 10 + (nptr[i++] - 48);
// 	return (res * sign);
// }

// static int	syntax_check(char *num)
// {
// 	int	i;

// 	i = 0;
// 	if (num[0] == '-' || num[0] == '+')
// 	{
// 		i++;
// 		if (num[i] == '"')
// 		{
// 			while (ft_isdigit(num[i]))
// 				i++;
// 			if (num[i] == '"')
// 				return (true);
// 			else
// 				return (false);
// 		}
// 	}
// 	while (num[i])
// 	{
// 		if (!ft_isdigit(num[i]))
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

void	ft_exit(char **cmds)
{
	if (cmds[2])
		ft_error("exit: too many arguments", 1);
	else if (!cmds[1])
		g_exit_status = 0;
	// else if (cmds[1] && syntax_check(cmds[1]))
	// 	g_exit_status = grep_only_num(cmds[1]) % 256;
	// else if (!syntax_check(cmds[1]))
	// 	ft_error("exit: numeric argument required", errno);
	//exit(g_exit_status);
}
