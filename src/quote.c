#include "../minishell.h"

char	**save_arg_to_clean(char *s, t_minishell *g_param)
{
	int		i;
	char	**temp;

	temp = NULL;
	i = 0;
	while (g_param->arg_to_clean[i])
		i++;
	i++;
	temp = malloc ((i + 1) * sizeof(char *));
	if (!temp)
	{
		ft_error("a malloc failed in save_arg_to_clean function", 1);
		return (NULL);
	}
	i = 0;
	while (g_param->arg_to_clean[i])
	{
		temp[i] = g_param->arg_to_clean[i];
		i++;
	}
	temp[i++] = s;
	temp[i] = NULL;
	free(g_param->arg_to_clean);
	g_param->arg_to_clean = NULL;
	return (temp);
}

void	skip_whitespace(char **cur, t_minishell *g_param)
{
	while (*cur < g_param->end_line && ft_strchr(" \t\n\v\r", **cur))
		(*cur)++;
}

int	quote_parsing(char **cur, int i, t_minishell *param, char *quote)
{
	while (**cur && (*quote != 'a' \
		|| (*quote == 'a' && !ft_strchr(" \t\n\v\r|><", **cur))))
	{
		if (*quote != '\'' && **cur == '$')
			dollars_parsing(cur, *quote, &i, param);
		else if (**cur == *quote && *quote != 'a')
		{
			*quote = 'a';
			(*cur)++;
			i++;
		}
		else if (*quote == 'a' && ft_strchr("'\"", **cur))
		{
			*quote = **cur;
			(*cur)++;
			i++;
		}
		else if (**cur)
		{
			*((*cur) - i) = **cur;
			(*cur)++;
		}
	}
	return (i);
}

void	dollars_parsing(char **cur, char quote, int *i, t_minishell *param)
{
	char	*s;
	char	*temp;

	temp = param->start_t;
	s = NULL;
	(*cur)++;
	if (ft_strchr(" \t\n\v\r", **cur))
	{
		(*cur)--;
		*((*cur) - *i) = **cur;
		(*cur)++;
		return;
	}
	*((*cur) - *i) = '\0';
		*i = 0;
	if (**cur == '?')
		s = dollars_exit(cur);
	else
		s = dollars_env(cur, quote, param);
	if (s)
	{

		temp = ft_strjoin(param->start_t, s);
		param->arg_to_clean = save_arg_to_clean(s, param);
	}
	else
		temp = ft_strdup(param->start_t);
	param->start_t = ft_strjoin(temp, *cur);
	*cur = param->start_t + ft_strlen(temp);
	param->end_line = *cur + ft_strlen(*cur);
	param->arg_to_clean = save_arg_to_clean(temp, param);
	param->arg_to_clean = save_arg_to_clean(param->start_t, param);
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
	free(s_redircmd);
	return (env);
}
