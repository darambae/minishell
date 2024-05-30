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
		printf("%s", argv[i]);
	if (n == 0)
		(printf("\n"));
	return(0);
}
/*
char	*get_paths(char **s, char *result)
{
	int		j;
	int		i;
	char	*path;
	char	*var;

	j = 0;
	i = 0;
	var = NULL;
	path = NULL;
	if (*s[j] == "$")
	{
		j++;
		while (*s[j] && *s[j] != "\"" && *s[j] != " ")
			var[i++] = *s[j++];
		var[i++] = "=";
		var[i] = '\0';
		*s = *(s + j);
	}
	j = 0;
	while (g_param->env_variables[j])
	{
		if (ft_strncmp(var, g_param->env_variables[j], 5) == 0)
			path = ft_strdup(g_param->env_variables[j] + ft_strlen(var + 1));
		j++;
	}
	path = ft_strjoin(result, path);
	return (path);
}
*/
