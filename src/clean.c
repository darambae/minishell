#include "../minishell.h"

int	is_executable(t_cmd *cmd, t_minishell *g_param)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *) cmd;
		if (pcmd->left->type == EXEC)
		{
			ecmd = (t_execcmd *) pcmd->left;
			if (!ecmd->argv[0])
				return (ft_error("minishell: syntax error near unexpected token '|'\n", g_param));
		}
		if (pcmd->right->type == EXEC)
		{
			ecmd = (t_execcmd *) pcmd->right;
			if (!ecmd->argv[0])
				return (ft_error("minishell: nothing after the pipe '|'\n", g_param));
		}
		if (pcmd->right->type == PIPE)
			return (is_executable(pcmd->right, g_param));
	}
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *) cmd;
		if (!ecmd->argv[0])
			return (0);
	}
	return (1);
}

void	free_cmd(t_cmd *cmd)
{
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;

	if (cmd->type == EXEC)
		free(cmd);
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *) cmd;
		if (rcmd->token == '{')
			unlink(rcmd->start_file);
		free_cmd(rcmd->cmd);
		free(cmd);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *) cmd;
		free_cmd(pcmd->left);
		free_cmd(pcmd->right);
		free(cmd);
	}
}

void	ft_clean_all(t_minishell *g_param)
{
	if (g_param)
	{
		if (g_param->first_cmd)
			free_cmd(g_param->first_cmd);
		free(g_param->cmd_line);
		g_param->stop = 0;
	}
}
