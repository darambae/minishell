#include "../minishell.h"

bool	pcmd_syntax_check(t_pipecmd *pcmd)
{
	t_execcmd	*ecmd;

	if (pcmd->left->type == EXEC)
	{
		ecmd = (t_execcmd *) pcmd->left;
		if (!ecmd->argv[0])
			return (false);
	}
	if (pcmd->right->type == EXEC)
	{
		ecmd = (t_execcmd *) pcmd->right;
		if (!ecmd->argv[0])
			return (false);
	}
	return (true);
}
//check if there is arg before and after pipe
int	is_executable(t_cmd *cmd, t_minishell *g_param)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *) cmd;
		if (!pcmd_syntax_check(pcmd))
			return (ft_error("syntax error near unexpected token '|'\n"));
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
	t_execcmd	*execcmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *) cmd;
		free(execcmd);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *) cmd;
		if (rcmd->token == '{')
			unlink(rcmd->start_file);
		free_cmd(rcmd->cmd);
		free(rcmd);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *) cmd;
		free_cmd(pcmd->left);
		free_cmd(pcmd->right);
		free(pcmd);
	}
}


void	ft_clean_all(t_minishell *g_param)
{
	if (g_param)
	{
		if (g_param->first_cmd)
		{
			free_cmd(g_param->first_cmd);
			g_param->first_cmd = NULL;
		}
		if (g_param->arg_to_clean)
			ft_free_tab(g_param->arg_to_clean);
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
			free(g_param->cmd_line);
		if (g_param->first_cmd)
		{
			free_cmd(g_param->first_cmd);
			g_param->first_cmd = NULL;
		}
		if (g_param->start_t)
		{
			free(g_param->start_t);
			g_param->start_t = NULL;
		}
		free(g_param);
		g_param = NULL;
		printf("exit\n");
		exit(0);
	}
}
