#include "../../minishell.h"

int	ft_env(char **argv, t_minishell *param)
{
	int	i;

	if (argv[1])
	{
		ft_error("env: too many arguments", errno);
		return (1);
	}
	i = 0;
	while (param->env_variables[i])
		printf("%s\n", param->env_variables[i++]);
	return (0);
}
