#include "../../minishell.h"

int	ft_env(char **argv, t_minishell *g_param)
{
	int	i;

	if (argv[1])
	{
		ft_error("env: too many arguments");
		return (1);
	}
	i = 0;
	while (g_param->env_variables[i])
		printf("%s\n", g_param->env_variables[i++]);
	return (0);
}
