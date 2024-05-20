
#include "../minishell.h"
/*Check a str through and skip whitespace. 
Set start_str on the non-whitespace char and check if it's a token.*/

bool	peek(char **start_str, char *end_str, char *c)
{
	char	*tmp;

	tmp = *start_str;
	while (tmp < end_str && ft_strchr(" \t\n\v\r", *tmp))
		tmp++;
	*start_str = tmp;
	return (*tmp && ft_strchr(c, *tmp));
}

int	get_token(char **start_line, char *end_line, char **start_t, char **end_t)
{
	char	*whitespace;
	char	*symbols;
	char	*cur;
	int		res;

	whitespace = " \t\n\v\r";
	symbols = "|><";
	cur = *start_line;
	res = 0;
	while (cur < end_line && ft_strchr(whitespace, *cur))
		cur++;
	if (start_t)
		*start_t = cur;
	res = *cur;
	if (*cur == '|')
		res = '-';
	else if (*cur == '<')
	{
		cur++;
		if (*cur == '<')
			res = '{'; //For <<
		else
			res = '['; //For <
	}
	else if (*cur == '>')
	{
		cur++;
		if (*cur == '>')
			res = '}'; //For >>
		else
			res = ']'; //For >
	}
	else
	{
		res = 'a'; //For any other argv including CMD, ARG, ETC,,,
		while (cur < end_line && !ft_strchr(whitespace, *cur) && !ft_strchr(symbols, *cur))
			cur++;
	}
	if (end_t)
		*end_t = cur;
	while (cur < end_line && ft_strchr(whitespace, *cur))
		cur++;
	*start_line = cur; //update where to start scanning
	return (res);
}
