#include "../minishell.h"

char	**create_double_arr(int size)
{
	char	**arr;
	int		i;

	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = NULL;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	len_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	ft_error(char *msg)
{
	errno = 1;
	perror(msg);
	//ft_putstr_fd(msg, 2);
	g_exit_status = EXIT_FAILURE;
	return (0);
}