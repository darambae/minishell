
#include "../minishell.h"

//Check a str through and skip whitespace. Set start_str on the non-whitespace char and check if it's a token.
bool	peek(char **start_str, char *end_str, char *c)
{
	char	*tmp;

	tmp = *start_str;
	while (tmp < end_str && ft_strchr(" \t\n\v\r", *tmp))
		tmp++;
	*start_str = tmp;
	return (*tmp && ft_strchr(c , *tmp));
}

bool	get_token(char **start_line, char **end_line, char **start_t, char **end_t)
{
	char	*whitespace;
	char	*symbols;
	char	*cur;
	int		token;

	whitespace = " \t\n\v\r";
	symbols = "$|><";
	cur = *start_line;
	while (*cur && ft_strchr(whitespace, *cur))
		cur++;
	if (!*cur)
		return (false);
	*start_t = cur;
	if (ft_strchr(symbols, *cur))
	{
		*end_t = cur + 1;
		*start_line = cur + 1;
		return (true);
	}
	while (*cur && !ft_strchr(whitespace, *cur) && !ft_strchr(symbols, *cur))
		cur++;
	*end_t = cur;
	*start_line = cur;
	return (true);
}