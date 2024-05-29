
#include "../minishell.h"

t_cmd	*parse_redire(t_cmd *cmd);

/*initialise an execcmd and fill argv[i] with option and args.
if redire, return an redirecmd wich point on the execcmd.
if no redire, return the execcmd*/
t_cmd	*parse_exec()
{
	t_cmd		*res;
	t_execcmd	*cmd;
	int			i;

	i = 0;
	res = execcmd();
	cmd = (t_execcmd *)res;
	res = parse_redire(res);
	while (peek("|") == 0 && g_param->start_line < g_param->end_line)
	{
		if (i >= 100)
			err_msg("too many args\n");
		if (!get_token(1))
			break ;
		cmd->argv[i] = g_param->start_t;
		cmd->end_argv[i] = g_param->end_t;
		i++;
		res = parse_redire(res);
	}
	cmd->argv[i] = 0;
	cmd->end_argv[i] = 0;
	return (res);
}
/*if no pipe, return an execcmd or a redirecmd.
if pipe, retturn a pipecmd wich left point to the first execcmd
and right point to the second execcmd or a second pipecmd etc...
at the end of parse_pipe, line is entirely parsed*/
t_cmd	*parse_pipe()
{
	t_cmd	*cmd;

	cmd = parse_exec();
	if (peek("|") && g_param->start_line < g_param->end_line)
	{
		get_token(0);
		cmd = pipecmd(cmd, parse_pipe());
	}
	return (cmd);
}

/*if no redire, return cmd; if redire, return a redircmd which point on cmd*/
t_cmd	*parse_redire(t_cmd *cmd)
{
	int		token;

	while (peek("<>") == 1 && g_param->start_line < g_param->end_line)
	{
		token = get_token(0);
		if(get_token(1) != 'a')
		{
			printf("minishell: syntax error near unexpected token '%s'\n", g_param->start_line);
			exit(1);
		}
		cmd = redircmd(cmd, token);
	}
	return (cmd);
}

t_cmd	*parse(char *line)
{
	t_cmd	*cmd;

	g_param->end_line = line + ft_strlen(line);
	g_param->start_line = line;
	cmd = parse_pipe();
	if (line != g_param->end_line)
		err_msg("syntax error\n");
	nul_terminator(cmd);
	return (cmd);
}
