#include "../minishell.h"

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

void	ft_clean_all(void)
{
	if (g_param)
	{
		if (g_param->first_cmd)
			free_cmd(g_param->first_cmd);
		free(g_param->cmd_line);
	}
}
