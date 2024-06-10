#include "../minishell.h"

static void	exec_nullset(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	int			i;

	execcmd = (t_execcmd *)cmd;
	i = 0;
	while (execcmd->argv[i])
		execcmd->end_argv[i++] = 0;
}

t_cmd	*nul_terminator(t_cmd *cmd)
{
	t_redircmd	*redircmd;
	t_pipecmd	*pipecmd;

	if (!cmd)
		return (0);
	if (cmd->type == EXEC)
		exec_nullset(cmd);
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

char	**create_double_arr(int size)
{
	char	**arr;
	int		i;

	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = NULL;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	len_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	ft_error(char *msg)
{
	errno = 1;
	perror(msg);
	//ft_putstr_fd(msg, 2);
	g_exit_status = EXIT_FAILURE;
	return (0);
}