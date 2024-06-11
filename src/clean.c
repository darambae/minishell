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

void	ft_clean_all(char *line, t_minishell *param)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (param)
	{
		if (param->first_cmd)
		{
			free_cmd(param->first_cmd);
			param->first_cmd = NULL;
		}
		if (param->arg_to_clean)
			ft_free_tab(param->arg_to_clean);
		if (param->cmd_line)
		{
			free(param->cmd_line);
			param->cmd_line = NULL;
		}
	}
}

void	handle_exit(char *line, t_minishell *param)
{
	if (line == NULL || ft_strcmp(line, "exit") == 0)
	{
		if (param->env_variables)
			ft_free_tab(param->env_variables);
		if (param->save_out)
			close(param->save_out);
		if (param->save_in)
			close(param->save_in);
		if (param->cmd_line)
		{
			free(param->cmd_line);
			param->cmd_line = NULL;
		}
		if (param->first_cmd)
		{
			free_cmd(param->first_cmd);
			param->first_cmd = NULL;
		}
		free(param);
		param = NULL;
		printf("exit\n");
		exit(0);
	}
}
