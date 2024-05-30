
#include "../minishell.h"

/*skip whitespace and tabs, return true if first carac == c or False if not
or if there is no carac
Set start_str on the next non-whitespace char and check if it's a token.*/
int	peek(char *c)
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
		(*cur)++;
		if (**cur == '<')
			*res = '{'; //For << (heredoc)
		else
			*res = '['; //For <
	}
	else if (**cur == '>')
	{
		(*cur)++;
		if (**cur == '>')
			*res = '}'; //For >> (append output)
		else
			*res = ']'; //For >
	}
	else
		*res = 'a'; //For any other argv including CMD, ARG, ETC,,,
}

void	skip_whitespace(char **cur)
{
	while (*cur < g_param->end_line && ft_strchr(" \t\n\v\r", **cur))
		(*cur)++;
}

/*set start_t on the next non whitespace char, indentify this char and
return a token (redire or word or pipe) and set start_line on the
non whitespace char after start_end*/
int	get_token(int save)
{
	char	*cur;
	int		res;
	char	quote;

	if (g_param->start_line >= g_param->end_line)
		return (0);
	cur = g_param->start_line;
	skip_whitespace(&cur);
	if (save)
		g_param->start_t = cur;
	give_token(&cur, &res);
	if (res == 'a')
	{
		if (*cur == '\'' || *cur == '"')
		{
			quote = *cur;
			cur++;
			if (save)
				g_param->start_t = cur;
			while (*cur && *cur != quote)
				cur++;
			if (*cur == '\0')
				err_msg("a quote is not closed");
			if (g_param->start_t == cur)
			{
				cur++;
				g_param->start_line = cur;
				return (get_token(save));
			}
		}
		else
		{
			while (cur < g_param->end_line && !ft_strchr(" \t\n\v\r", *cur) \
				&& !ft_strchr("|><", *cur))
				cur++;
		}
		//check $ sign
	}
	else
		cur++;
	if (save)
		g_param->end_t = cur;
	skip_whitespace(&cur);
	g_param->start_line = cur;
	if (g_param->start_t && g_param->end_t && *(g_param->end_t))
		*(g_param->end_t) = '\0';
	return (res);
}
