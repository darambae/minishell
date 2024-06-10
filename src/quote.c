#include "../minishell.h"

void	skip_whitespace(char **cur, t_minishell *g_param)
{
	while (*cur < g_param->end_line && ft_strchr(" \t\n\v\r", **cur))
		(*cur)++;
}

int	quote_parsing(char *cur, int save, char quote, t_minishell *g_param)
{
	cur++;
	if (save)
		g_param->start_t = cur;
	while (*cur && *cur != quote)
	{
		if (quote == '"' && *cur == '$')
			return (dollars_parsing(cur, save, quote, g_param));
		cur++;
	}
	if (*cur == '\0')
		return (ft_error("a quote is not closed\n"));
	if (g_param->start_t == cur)
	{
		cur++;
		g_param->start_line = cur;
		return (get_token(save, g_param));
	}
	if (save)
		g_param->end_t = cur;
	skip_whitespace(&cur, g_param);
	g_param->start_line = cur;
	if (g_param->start_t && g_param->end_t && *(g_param->end_t))
		*(g_param->end_t) = '\0';
	return ('a');
}

int	dollars_parsing(char *cur, int save, char quote, t_minishell *g_param)
{
	char	*s;

	s = cur;
	s++;
	if (*s == '?')
	{
		s++;
		cur = s;
		s = ft_itoa(g_exit_status);
	}
	else
	{
		while (cur < g_param->end_line && !ft_strchr(" \t\n\v\r", *cur) \
				&& *cur != quote)
			cur++;
		*cur = '\0';
		s = get_path(ft_strjoin(s, "="), g_param);
		cur++;
	}
	g_param->start_line = cur;
	if (!s)
		return (get_token(save, g_param));
	g_param->start_t = s;
	g_param->end_t = s + strlen(s);
	return ('a');
}

char	*get_path(char *s_redircmd, t_minishell *g_param)
{
	int		j;
	char	*env;
	int		len;

	j = 0;
	len = ft_strlen(s_redircmd);
	env = NULL;
	while (g_param->env_variables[j])
	{
		if (ft_strncmp(s_redircmd, g_param->env_variables[j], len) == 0)
		{
			env = ft_strdup(g_param->env_variables[j] + len);
			break ;
		}
		j++;
	}
	if (!env)
	{
		free(env);
		return (NULL);
	}
	return (env);
}
