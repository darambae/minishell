#include "../../minishell.h"

int	ft_env(char **argv)
{
	int	i;
    
    if (argv[1])
    {
        errno = 1;
        perror("Invalid");
        return (1);
    }
    i = 0;
	while (g_param->env_variables[i])
		printf("%s\n", g_param->env_variables[i++]);
    return (0);
}