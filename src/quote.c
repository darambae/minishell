#include "../minishell.h"

int	quote_parsing(char **cur, int save, char quote)
{
	(*cur)++;
	if (save)
		g_param->start_t = *cur;
	while (**cur && **cur != quote)
	{
		if (quote == '"' && **cur == '$')
			return (dollars_parsing(cur, save, quote));
		(*cur)++;
	}
	if (**cur == '\0')
		err_msg("a quote is not closed");
	if (g_param->start_t == *cur)
	{
		(*cur)++;
		g_param->start_line = *cur;
		return (get_token(save));
	}
	if (save)
		g_param->end_t = *cur;
	skip_whitespace(cur);
	g_param->start_line = *cur;
	if (g_param->start_t && g_param->end_t && *(g_param->end_t))
		*(g_param->end_t) = '\0';
	return ('a');
}

int	dollars_parsing(char **cur, int save, char quote)
{
	char	*s;

	s = *cur;
	s++;
	if (*s == '?')
	{
		s++;
		*cur = s;
		s = ft_itoa(g_param->exit_status);
	}
	else
	{
		while (s < g_param->end_line && !ft_strchr(" \t\n\v\r", *s) \
				&& *s != quote)
			s++;
		*cur = s;
		*s = '\0';
		(*cur)++;
		s = get_path(ft_strjoin(s, "="));
	}
	g_param->start_line = *cur;
	if (!s)
		return (get_token(save));
	g_param->start_t = s;
	g_param->end_t = s + strlen(s);
	return ('a');
}

char	*get_path(char *s)
{
	int		j;
	char	*env;
	int		len;

	j = 0;
	len = ft_strlen(s);
	while (g_param->env_variables[j])
	{
		if (ft_strncmp(s, g_param->env_variables[j], len) == 0)
			env = ft_strdup(g_param->env_variables[j] + len);
		j++;
	}
	if (!env)
	{
		free(env);
		return (NULL);
	}
	return (env);
}
