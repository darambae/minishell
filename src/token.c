
#include "../minishell.h"

/*Check a str through and skip whitespace. 
Set start_str on the non-whitespace char and check if it's a token.*/

int	peek(char **start_str, char *end_str, char *c)
{
	char	*tmp;

	tmp = *start_str;
	while (tmp < end_str && ft_strchr(" \t\n\v\r", *tmp))
		tmp++;
	*start_str = tmp;
	if (tmp == end_str)
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

void	skip_whitespace(char **cur, char *end_line)
{
	while (*cur < end_line && ft_strchr(" \t\n\v\r", **cur))
		(*cur)++;
}

int	get_token(char **start_line, char *end_line, char **start_t, char **end_t)
{
	char	*cur;
	int		res;

	if (*start_line >= end_line)
		return (0);
	cur = *start_line;
	skip_whitespace(&cur, end_line);
	if (start_t)
		*start_t = cur;
	give_token(&cur, &res);
	if (res == 'a')
	{
		while (cur < end_line && !ft_strchr(" \t\n\v\r", *cur) \
			&& !ft_strchr("|><", *cur))
			cur++;
		//check if it's an argument or command
	}
	else
		cur++;
	if (end_t)
		*end_t = cur;

	skip_whitespace(&cur, end_line);
	*start_line = cur;
	if (start_t && end_t && *end_t)
		**end_t = '\0';
	return (res);
}
