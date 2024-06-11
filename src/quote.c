#include "../minishell.h"

void	skip_whitespace(char **cur, t_minishell *param)
{
	while (*cur < param->end_line && ft_strchr(" \t\n\v\r", **cur))
		(*cur)++;
}

int	quote_parsing(char *cur, int save, char quote, t_minishell *param)
{
	cur++;
	if (save)
		param->start_t = cur;
	while (*cur && *cur != quote)
	{
		if (quote == '"' && *cur == '$')
			return (dollars_parsing(cur, save, quote, param));
		cur++;
	}
	if (*cur == '\0')
		return (ft_error("a quote is not closed", 1));
	if (param->start_t == cur)
	{
		cur++;
		param->start_line = cur;
		return (get_token(save, param));
	}
	if (save)
		param->end_t = cur;
	skip_whitespace(&cur, param);
	param->start_line = cur;
	if (param->start_t && param->end_t && *(param->end_t))
		*(param->end_t) = '\0';
	return ('a');
}

int	dollars_parsing(char *cur, int save, char quote, t_minishell *param)
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
		while (cur < param->end_line && !ft_strchr(" \t\n\v\r", *cur) \
				&& *cur != quote)
			cur++;
		*cur = '\0';
		s = get_path(ft_strjoin(s, "="), param);
		cur++;
	}
	param->start_line = cur;
	if (!s)
		return (get_token(save, param));
	param->start_t = s;
	param->end_t = s + strlen(s);
	return ('a');
}

char	*get_path(char *s_redircmd, t_minishell *param)
{
	int		j;
	char	*env;
	int		len;

	j = 0;
	len = ft_strlen(s_redircmd);
	env = NULL;
	while (param->env_variables[j])
	{
		if (ft_strncmp(s_redircmd, param->env_variables[j], len) == 0)
		{
			env = ft_strdup(param->env_variables[j] + len);
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
