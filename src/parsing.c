#include "../minishell.h"

t_cmd	*parse_redire(t_cmd *cmd, t_minishell *param);

/*initialise an execcmd and fill argv[i] with option and args.
if redire, return an redirecmd wich point on the execcmd.
if no redire, return the execcmd*/
t_cmd	*parse_exec(t_minishell *param)
{
	t_cmd		*res;
	t_execcmd	*cmd;
	int			i;

	i = 0;
	res = execcmd();
	cmd = (t_execcmd *)res;
	res = parse_redire(res, param);
	while (peek("|", param) == 0 && param->start_line < param->end_line)
	{
		if (i >= 100)
			perror("too many args\n");
		if (!get_token(1, param))
			break ;
		cmd->argv[i] = param->start_t;
		cmd->end_argv[i] = param->end_t;
		i++;
		res = parse_redire(res, param);
		if (!res)
			return (NULL);
	}
	cmd->argv[i] = 0;
	cmd->end_argv[i] = 0;
	return (res);
}
/*if no pipe, return an execcmd or a redirecmd.
if pipe, retturn a pipecmd wich left point to the first execcmd
and right point to the second execcmd or a second pipecmd etc...
at the end of parse_pipe, line is entirely parsed*/

t_cmd	*parse_pipe(t_minishell *param)
{
	t_cmd	*cmd;

	cmd = parse_exec(param);
	if (peek("|", param) && param->start_line < param->end_line)
	{
		get_token(0, param);
		cmd = pipecmd(cmd, parse_pipe(param));
	}
	return (cmd);
}

/*if no redire, return cmd; if redire, return a redircmd which point on cmd*/
t_cmd	*parse_redire(t_cmd *cmd, t_minishell *param)
{
	int		token;

	while (peek("<>", param) == 1 && param->start_line < param->end_line)
	{
		token = get_token(0, param);
		if (get_token(1, param) != 'a')
			ft_error("minishell: syntax error near unexpected token", 1);
		cmd = redircmd(cmd, token, param);
	}
	return (cmd);
}

t_cmd	*parse(t_minishell *param)
{
	t_cmd	*cmd;

	cmd = parse_pipe(param);
	if (!cmd)
		return (NULL);
	if (param->start_line < param->end_line)
		ft_error("syntax error", 1);
	nul_terminator(cmd);
	return (cmd);
}
