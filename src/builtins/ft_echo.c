#include "../../minishell.h"

//print the string after the cmd echo
int	ft_echo(char **argv)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (ft_strncmp(argv[i], "-n ", 3) == 0)
	{
		n = 1;
		i++;
	}
	while (argv[i])
		printf("%s", argv[i++]);
	if (n == 0)
		(printf("\n"));
	return (0);
}

