#include "../../minishell.h"

//print the string after the cmd echo
void	ft_echo(char **cmd)
{
	char	*s;

	s = check_cmd(cmd);
	if (s == NULL)
		exit(printf("\n"));
	exit(printf("%s", s));
}
//clean the string after the cmd echo
char	*check_cmd(char **cmd)
{
	char	*s;
	char	*result;
	int		i;
	char	end;

	end = "\n";
	i = 1;
	s = cmd[i];
	while (s)
	{
		i++;
		if (*s == '-')
		{
			if (*(s + 1) == 'n' && (*(s + 2) == " " || *(s + 0) == "\0"))
			{
				end = "\0";
				s = s + 2;
			}
		}
		result = ft_strjoin(result, )


		result = del_multiple_char(result, s, " ");
	}
}
char	*check_quote(char *s)
{
	char	*result;
	int	i;

	i = 0;
	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s)
	{
		if (*s == "\'")
			keep_between_quote(result, &s, "\'", &i);
		else if (*s == "\"")
			keep_between_quote(result, &s, "\"", &i);
		else if (*s && *s != "\"" && *s != "\'")
			result[i] = *s++;
	}
	result[i] = '\0';
	return (result);
}

void	keep_between_quote(char *result, char **argv, char c, int *i)
{
	char	*s;

	s = *argv;
	s++;
	while (*s && *s != c)
	{
		if (c == "\"" && *s == "$")
		{
			result[*i] = "\0";
			result = get_path(&s, result);
		}
		result[*i++] = s++;
		if (!*s)
			ft_error("single quote not closed");
		s++;
	}
	*argv = s;
}

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
