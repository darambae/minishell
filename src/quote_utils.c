#include "../minishell.h"

char	*dollars_exit(char **cur)
{
	char	*s;

	s = NULL;
	(*cur)++;
	s = ft_itoa(g_exit_status);
	return (s);
}

char	*dollars_env(char **cur, char quote, t_minishell *param)
{
	char	*s;
	int		i;
	char	*temp;

	i = 0;
	s = ft_strdup(*cur);
	while (*cur < param->end_line && !ft_strchr(" \t\n\v\r|><", **cur) \
				&& (**cur != quote || quote == 'a'))
	{
		(*cur)++;
		i++;
	}
	s[i] = '\0';
	temp = s;
	s = get_path(ft_strjoin(s, "="), param);
	free(temp);
	return (s);
}
