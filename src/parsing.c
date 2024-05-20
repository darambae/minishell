
#include "../minishell.h"

int	parse(char *line)
{
	char	*end_line;
	t_cmd	*cmd;

	end_line = line + ft_strlen(line);
	cmd = parse_redire(cmd, &line, end_line);

}

t_cmd	*parse_pipe(t_cmd *cmd, char **start_line, char *end_line)
{
	char	*start_t;
	char	*end_t;
	int		token;

	cmd = parse_redire(cmd, start_line, end_line);
	while (peek(start_line, end_line, "|"))
	{
		get_token(start_line, end_line, &start_t, &end_t);
		cmd = pipecmd(cmd, parse_redire(0, start_t, end_t));
	}
	return (cmd);
}

t_cmd	*parse_redire(t_cmd *cmd, char **start_line, char *end_line)
{
	char	*start_t;
	char	*end_t;
	int		token;

	start_t = 0;
	end_t = 0;
	while (peek(start_line, end_line, "<>"))
	{
		token = get_token(start_line, end_line, &start_t, &end_t);
		if (token == '[')
			cmd = redircmd(cmd, start_t, end_t, O_RDONLY, 0);
		else if (token == ']')
			cmd = redircmd(cmd, start_t, end_t, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (token == '{')
			cmd = redircmd(cmd, start_t, end_t, O_RDONLY, 0);
		else if (token == '}')
			cmd = redircmd(cmd, start_t, end_t, O_WRONLY | O_CREAT | O_APPEND, 1);
	}
	return (cmd);
}