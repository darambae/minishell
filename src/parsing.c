
#include "../minishell.h"

t_cmd	*parse_redire(t_cmd *cmd, t_minishell *g_param);

/*initialise an execcmd and fill argv[i] with option and args.
if redire, return an redirecmd wich point on the execcmd.
if no redire, return the execcmd*/
t_cmd	*parse_exec(t_minishell *g_param)
{
	t_cmd		*res;
	t_execcmd	*cmd;
	int			i;

	i = 0;
	res = execcmd();
	cmd = (t_execcmd *)res;
	res = parse_redire(res, g_param);
	while (peek("|", g_param) == 0 && g_param->start_line < g_param->end_line)
	{
		if (i >= 100)
			perror("too many args\n");
		if (!get_token(1, g_param))
			break ;
		cmd->argv[i] = g_param->start_t;
		cmd->end_argv[i] = g_param->end_t;
		i++;
		res = parse_redire(res, g_param);
	}
	cmd->argv[i] = 0;
	cmd->end_argv[i] = 0;
	return (res);
}
/*if no pipe, return an execcmd or a redirecmd.
if pipe, retturn a pipecmd wich left point to the first execcmd
and right point to the second execcmd or a second pipecmd etc...
at the end of parse_pipe, line is entirely parsed*/

t_cmd	*parse_pipe(t_minishell *g_param)
{
	t_cmd	*cmd;

	cmd = parse_exec(g_param);
	if (peek("|", g_param) && g_param->start_line < g_param->end_line)
	{
		get_token(0, g_param);
		cmd = pipecmd(cmd, parse_pipe(g_param));
	}
	return (cmd);
}

/*if no redire, return cmd; if redire, return a redircmd which point on cmd*/
t_cmd	*parse_redire(t_cmd *cmd, t_minishell *g_param)
{
	int		token;

	while (peek("<>", g_param) == 1 && g_param->start_line < g_param->end_line)
	{
		token = get_token(0, g_param);
		if (get_token(1, g_param) != 'a')
			ft_error("minishell: syntax error near unexpected token \n");
		cmd = redircmd(cmd, token, g_param);
	}
	return (cmd);
}

t_cmd	*parse(t_minishell *g_param)
{
	t_cmd	*cmd;

	cmd = parse_pipe(g_param);
	if (g_param->start_line < g_param->end_line)
		ft_error("syntax error\n");
	nul_terminator(cmd);
	return (cmd);
}
