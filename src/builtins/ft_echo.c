#include "../../minishell.h"

//print the string after the cmd echo
void	ft_echo(char **cmd)
{
	char	*s;

	s = check_cmd(cmd);
	if (s == NULL)
		exit(printf("\n"));
	exit(printf("%s", s));
}
//clean the string after the cmd echo
char	*check_cmd(char **cmd)
{
	char	*s;
	char	*result;
	int		i;
	int	squote;
	int	dquote;
	char	end;

	end = "\n";
	i = 1;
	s = cmd[i];
	if (s)
	{
		i++;
		if (*s == '-')
		{
			s++;
			if (*s == 'n' && (*(s + 1) == " " || *(s + 1) == "\0"))
				end = "\0";
		}
		while (*s == '\'' || *s =='\"')
		{
			if (*s == '\'')
				squote++;
			else if (*s == '\"')
				dquote++;
			*s = " ";
			s++;
		}
		while (*s)
		{
			if (*s == '\'' && squote > 0)
				*s = " ";
			if(*s =='\"' && dquote > 0)
				*s = " ";
			s++;
		}
		result = del_multiple_char(result, s, " ");
	}
}
char	*check_quote(char *s)
{
	char	*result;
	int	i;

	i = 0;
	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s)
	{
		if (*s == "\'")
			keep_between_quote(result, &s, "\'", &i);
		else if (*s == "\"")
			keep_between_quote(result, &s, "\"", &i);
		else if (*s && *s != "\"" && *s != "\'")
			result[i] = *s++;
	}
	result[i] = '\0';
	return (result);
}

void	keep_between_quote(char *result, char **argv, char c, int *i)
{
	char	*s;

	s = *argv;
	s++;
	while (*s && *s != c)
	{
		if (*s == "$")
		{
			result[*i] = "\0";
			result = get_path(&s, result);
		}
		result[*i++] = s++;
		if (!*s)
			ft_error("single quote not closed");
		s++;
	}
	*argv = s;
}

