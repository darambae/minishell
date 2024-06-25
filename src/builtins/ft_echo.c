#include "../../minishell.h"

void	return_line(char **argv, int *i, int *n)
{
	int	j;

	j = 2;
	while (argv[*i] && ft_strncmp(argv[*i], "-n", 2) == 0)
	{
		j = 2;
		while (argv[*i][j] == 'n')
			j++;
		if (!argv[*i][j])
		{
			*n = 1;
			(*i)++;
		}
		else
			break ;
	}
}

//print the string after the cmd echo
int	ft_echo(char **argv)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	return_line(argv, &i, &n);
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (n == 0)
		printf("\n");
	return (0);
}
