
#include "../minishell.h"

t_cmd	*parse_redire(t_cmd *cmd, char **start_line, char *end_line);

t_cmd	*parse_exec(char **start_line, char *end_line)
{
	t_cmd		*res;
	t_execcmd	*cmd;
	char		*start_t;
	char		*end_t;
	int			token;
	int 		i;

	i = 0;
	start_t = 0;
	end_t = 0;
	res = execcmd();
	cmd = (t_execcmd *)res;
	while (peek(start_line, end_line, "|") == 0 && *start_line < end_line)
	{
		token = get_token(start_line, end_line, &start_t, &end_t);
		if (!token)
			break ;
		cmd->argv[i] = start_t;
		cmd->end_argv[i] = end_t;
		i++;
		if (i >= 100)
			err_msg("too many args\n");
	}
	cmd->argv[i] = 0;
	cmd->end_argv[i] = 0;
	res = parse_redire(res, start_line, end_line);
	return (res);
}

t_cmd	*parse_pipe(char **start_line, char *end_line)
{
	t_cmd	*cmd;

	cmd = parse_exec(start_line, end_line);
	if (peek(start_line, end_line, "|") && *start_line < end_line)
	{
		get_token(start_line, end_line, 0, 0);
		cmd = pipecmd(cmd, parse_pipe(start_line, end_line));
	}
	return (cmd);
}

t_cmd	*parse_redire(t_cmd *cmd, char **start_line, char *end_line)
{
	char	*start_t;
	char	*end_t;
	int		token;

	while (peek(start_line, end_line, "<>") == 1 && *start_line < end_line)
	{
		token = get_token(start_line, end_line, &start_t, &end_t);
		if (token != 'a')
			err_msg("missing file for redirection\n");
		if (token == '[')
			cmd = redircmd(cmd, start_t, end_t, O_RDONLY);
		else if (token == ']')
			cmd = redircmd(cmd, start_t, end_t, O_WRONLY | O_CREAT | O_TRUNC);
		else if (token == '{')
			cmd = redircmd(cmd, start_t, end_t, O_RDONLY);
		else if (token == '}')
			cmd = redircmd(cmd, start_t, end_t, O_WRONLY | O_CREAT | O_APPEND);
	}
	return (cmd);
}

t_cmd	*parse(char *line)
{
	char	*end_line;
	t_cmd	*cmd;

	end_line = line + ft_strlen(line);
	cmd = parse_pipe(&line, end_line);
	if (line != end_line)
		err_msg("syntax error\n");
	nul_terminator(cmd);
	return (cmd);
}