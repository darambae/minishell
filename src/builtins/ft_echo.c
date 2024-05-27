#include "../../minishell.h"

//print the string after the cmd echo
void	ft_echo(char **cmd)
{
	char	*s;

	s = check_cmd(cmd);
	ft_printf("%s", s);
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
			if (*s == 'n')
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

char	*del_multiple_char(char *result, char *s, char c)
{}
