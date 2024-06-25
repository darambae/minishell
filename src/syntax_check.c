#include "../minishell.h"

static bool	pcmd_syntax_check(t_pipecmd *pcmd)
{
	t_execcmd	*ecmd;

	if (!pcmd->left || !pcmd->right)
		return (false);
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

int	is_executable(t_cmd *cmd, t_minishell *param)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *) cmd;
		if (!pcmd_syntax_check(pcmd))
			ft_error("syntax error near unexpected token '|'", errno);
		if (pcmd->right->type == PIPE || pcmd->right->type == EXEC)
			return (is_executable(pcmd->right, param));
	}
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *) cmd;
		if (!ecmd->argv[0] || (!*(ecmd->argv[0]) && !ecmd->argv[1]))
			return (0);
	}
	return (1);
}
