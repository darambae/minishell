
#include "../minishell.h"

t_cmd	*execcmd(void)
{
	t_execcmd	*execcmd;

	execcmd = (t_execcmd *)malloc(sizeof(*execcmd));
	ft_memset(execcmd, 0, sizeof(*execcmd));
	execcmd->type = EXEC;
	return ((t_cmd *)execcmd);
}

t_cmd	*redircmd(t_cmd *sub_cmd, char *s_file, char *e_file, int mode, int fd)
{
	t_redircmd	*redircmd;

	redircmd = (t_redircmd *)malloc(sizeof(*redircmd));
	ft_memset(redircmd, 0, sizeof(*redircmd));
	redircmd->type = REDIR;
	redircmd->cmd = sub_cmd;
	redircmd->start_file = s_file;
	redircmd->end_file = e_file;
	redircmd->mode = mode;
	redircmd->fd = fd;
	return ((t_cmd *)redircmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*pipecmd;

	pipecmd = (t_pipecmd *)malloc(sizeof(*pipecmd));
	ft_memset(pipecmd, 0, sizeof(*pipecmd));
	pipecmd->type = PIPE;
	pipecmd->left = left;
	pipecmd->right = right;
	return ((t_cmd *)pipecmd);
}
t_cmd	*nul_terminator(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	t_redircmd	*redircmd;
	t_pipecmd	*pipecmd;
	int			i;

	if (!cmd)
		return (0);
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		i = 0;
		while (execcmd->argv[i])
			execcmd->end_argv[i++] = 0;
	}
	else if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		nul_terminator(redircmd->cmd);
		*redircmd->end_file = 0;
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		nul_terminator(pipecmd->left);
		nul_terminator(pipecmd->right);
	}
	return (cmd);
}