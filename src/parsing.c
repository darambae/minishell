
#include "../minishell.h"

t_cmd	*parse_redire(t_cmd *cmd, char **start_line, char *end_line);

t_cmd	*parse_exec(char **start_line, char *end_line)
{
	t_cmd		*res;
	t_execcmd	*cmd;
	char		*start_t;
	char		*end_t;
	int			i;

	i = 0;
	res = execcmd();
	cmd = (t_execcmd *)res;
	res = parse_redire(res, start_line, end_line);
	while (peek(start_line, end_line, "|") == 0 && *start_line < end_line)
	{
		if (i >= 100)
			err_msg("too many args\n");
		if (!get_token(start_line, end_line, &start_t, &end_t))
			break ;
		cmd->argv[i] = start_t;
		cmd->end_argv[i] = end_t;
		i++;
		res = parse_redire(res, start_line, end_line);
	}
	cmd->argv[i] = 0;
	cmd->end_argv[i] = 0;
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
	
	start_t = 0;
	end_t = 0;
	while (peek(start_line, end_line, "<>") == 1 && *start_line < end_line)
	{
		token = get_token(start_line, end_line, 0, 0);
		//check if the word that start_t is pointing at is cmd or not
		//if (check_filename(start_line, &start_t, &end_t) == false)
		//	err_msg("missing filename");
		cmd = redircmd(cmd, start_t, end_t, token);
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