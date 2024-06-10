#include "../minishell.h"

static void	free_rcmd(t_cmd *cmd)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *) cmd;
	if (rcmd->token == '{')
		unlink(rcmd->start_file);
	free_cmd(rcmd->cmd);
	free(rcmd);
}

void	free_cmd(t_cmd *cmd)
{
	t_pipecmd	*pcmd;
	t_execcmd	*execcmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *) cmd;
		free(execcmd);
	}
	else if (cmd->type == REDIR)
		free_rcmd(cmd);
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *) cmd;
		free_cmd(pcmd->left);
		free_cmd(pcmd->right);
		free(pcmd);
	}
	else
		free(cmd);
}

void	ft_clean_all(char *line, t_minishell *g_param)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (g_param)
	{
		if (g_param->first_cmd)
		{
			free_cmd(g_param->first_cmd);
			g_param->first_cmd = NULL;
		}
		if (g_param->cmd_line)
		{
			free(g_param->cmd_line);
			g_param->cmd_line = NULL;
		}
	}
}

void	handle_exit(char *line, t_minishell *g_param)
{
	if (line == NULL || ft_strcmp(line, "exit") == 0)
	{
		if (g_param->env_variables)
			ft_free_tab(g_param->env_variables);
		if (g_param->save_out)
			close(g_param->save_out);
		if (g_param->save_in)
			close(g_param->save_in);
		if (g_param->cmd_line)
		{
			free(g_param->cmd_line);
			g_param->cmd_line = NULL;
		}
		if (g_param->first_cmd)
		{
			free_cmd(g_param->first_cmd);
			g_param->first_cmd = NULL;
		}
		free(g_param);
		g_param = NULL;
		printf("exit\n");
		exit(0);
	}
}
