
#include "../minishell.h"

/*skip whitespace and tabs, return true if first carac == c or False if not
or if there is no carac
Set start_str on the next non-whitespace char and check if it's a token.*/
int	peek(char *c, t_minishell *g_param)
{
	char	*tmp;

	tmp = g_param->start_line;
	while (tmp < g_param->end_line && ft_strchr(" \t\n\v\r", *tmp))
		tmp++;
	g_param->start_line = tmp;
	if (tmp == g_param->end_line)
		return (-1);
	return (*tmp && ft_strchr(c, *tmp));
}

void	give_token(char **cur, int *res)
{
	*res = **cur;
	if (!**cur)
		*res = 0;
	else if (**cur == '|')
		*res = '-';
	else if (**cur == '<')
	{
		if (*(*cur + 1) == '<')
			{
				(*cur)++;
				*res = '{'; //For << (heredoc)
			}
		else
			*res = '['; //For <
	}
	else if (**cur == '>')
	{
		if (*(*cur + 1) == '>')
		{
			(*cur)++;
			*res = '}'; //For >> (append output)
		}
		else
			*res = ']'; //For >
	}
	else
		*res = 'a'; //For any other argv including CMD, ARG, ETC,,,
}

void	skip_whitespace(char **cur, t_minishell *g_param)
{
	while (*cur < g_param->end_line && ft_strchr(" \t\n\v\r", **cur))
		(*cur)++;
}

/*set start_t on the next non whitespace char, indentify this char and
return a token (redire or word or pipe) and set start_line on the
non whitespace char after start_end*/
int	get_token(int save, t_minishell *g_param)
{
	char	*cur;
	int		res;

	if (g_param->start_line >= g_param->end_line)
		return (0);
	cur = g_param->start_line;
	skip_whitespace(&cur, g_param);
	if (save)
		g_param->start_t = cur;
	give_token(&cur, &res);
	if (res == 'a')
	{
		if (*cur == '$')
			return (dollars_parsing(cur, save, '\0', g_param));
		if (*cur == '\'' || *cur == '"')
			return (quote_parsing(cur, save, *cur, g_param));
		while (cur < g_param->end_line && !ft_strchr(" \t\n\v\r", *cur) \
			&& !ft_strchr("|><$", *cur))
			cur++;
	}
	else
		cur++;
	if (save)
		g_param->end_t = cur;
	skip_whitespace(&cur, g_param);
	g_param->start_line = cur;
	if (g_param->start_t && g_param->end_t && *(g_param->end_t))
		*(g_param->end_t) = '\0';
	return (res);
}
