#include "../minishell.h"

int	quote_parsing(char **cur, int save)
{
	char	quote;

	quote = **cur;
	(*cur)++;
	if (save)
		g_param->start_t = *cur;
	while (**cur && **cur != quote)
		(*cur)++;
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
/*
int quote_position(char *line, int last)
{
	char	*double_quote;
	char	*single_quote;

	if (last)
	{
		double_quote = ft_strrchr(line, '"');
		single_quote = ft_strrchr(line, '\'');
	}
	else
	{
		double_quote = ft_strchr(line, '"');
		single_quote = ft_strchr(line, '\'');
	}
	if (!double_quote && !single_quote)
		return (0);  // Neither quote found
	else if (!double_quote && single_quote)
		return (1);  // Single quote found
	else if (double_quote && !single_quote)
		return (2);  // Double quote found
	if ((!last && double_quote < single_quote) || (last && double_quote > single_quote))
		return (2);  // Double quote appears first/last
	else if ((!last && single_quote < double_quote) || (last && double_quote < single_quote))
		return (1);  // Single quote appears first/last
	else
		return (-1);
}

bool    check_closed_quotes(char *line, int num_double, int num_single)
{
	int first_pos;
	int last_pos;

	first_pos = quote_position(line, 0);
	last_pos = quote_position(line, 1);
	// Check if any quote exists
	if (first_pos == 0)
		return (true); // No quote found, so they are closed
	//Check if first and last quote positions are the same and the num of the quotes are even number
	if ((first_pos == 2 && last_pos == 2 && num_double % 2 == 0) || \
		(first_pos == 1 && last_pos == 1 && num_single % 2 == 0))
		return (true); // All quotes are closed
	else
		return (false); // Quotes are not closed
}

bool	valid_quote(char *line)
{
	int	num_double;
	int	num_single;

	num_double = ft_count_char(line, '"');
	num_single = ft_count_char(line, '\'');
	if (num_double % 2 != 0 && num_single % 2 != 0)
		return (false);
	else
		return (check_closed_quotes(line, num_double, num_single));
}

//need to free later.
char	*remove_quotes(char *word)
{
	char	*res;
	int		num_quotes;
	int		i;

	num_quotes = ft_count_char(word, '\'') + ft_count_char(word, '\"');
	res = malloc(sizeof(char *) * (ft_strlen(word) - num_quotes + 1));
	i = 0;
	while (*word)
	{
		if (*word != '\'' && *word != '\"')
		{
			res[i] = *word;
			i++;
		}
		word++;
	}
	return (res);
}
*/
