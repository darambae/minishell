
#include "../minishell.h"

t_cmd	*parse_redire(t_cmd *cmd, char **start_line, char *end_line);

/*initialise an execcmd and fill argv[i] with option and args.
if redire, return an redirecmd wich point on the execcmd.
if no redire, return the execcmd*/
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
/*if no pipe, return an execcmd or a redirecmd.
if pipe, retturn a pipecmd wich left point to the first execcmd
and right point to the second execcmd or a second pipecmd etc...
at the end of parse_pipe, line is entirely parsed*/
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

/*if no redire, return cmd; if redire, return a redircmd which point on cmd*/
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
		if(get_token(start_line, end_line, &start_t, &end_t) != 'a')
		{
			printf("minishell: syntax error near unexpected token '%s'\n", *start_line);
			exit(1);
		}
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
