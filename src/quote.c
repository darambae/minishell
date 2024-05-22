#include "../minishell.h"

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

int		count_quotes(char *line, char quote)
{
	int     count;

	count = 0;
	while (*line)
	{
		if (*line == quote)
			count++;
		line++;
	}
	return (count);
}

bool    check_closed_quotes(char *line, int num_double, int num_single)
{
	int first_pos;
	int last_pos;

	first_pos = quote_position(line, 0);
	last_pos = quote_position(line, 1);
	// Check if any quote exists
	if (first_pos == 0)
		return true; // No quote found, so they are closed
	//Check if first and last quote positions are the same and the num of the quotes are even number
	if ((first_pos == 2 && last_pos == 2 && num_double % 2 == 0) || \
		(first_pos == 1 && last_pos == 1 && num_single % 2 == 0))
		return true; // All quotes are closed
	else
		return false; // Quotes are not closed
}

bool	valid_quote(char *line)
{
	int	num_double;
	int	num_single;

	num_double = count_quotes(line, '"');
	num_single = count_quotes(line, '\'');
	if (num_double % 2 != 0 && num_single % 2 != 0)
		return (false);
	else
		return (check_closed_quotes(line, num_double, num_single));
}