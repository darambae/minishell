#include "../minishell.h"

//temporary functions to get path
static char	**whole_paths(char **envp)
{
	int		j;
	char	*whole_path;
	char	**path_arr;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp("PATH=", envp[j], 5) == 0)
		{
			whole_path = ft_strdup(envp[j] + 5);
			path_arr = ft_split(whole_path, ':');
		}
		j++;
	}
	free(whole_path);
	if (!path_arr)
	{
		ft_free_tab(path_arr);
		return (NULL);
	}
	return (path_arr);
}

char	*get_cmd_path(char *cmd_name, char **envp)
{
	int		j;
	char	*cmd_path;
	char	*tmp;
	char	**path_arr;

	path_arr = whole_paths(envp);
	j = 0;
	while (path_arr[j])
	{
		tmp = ft_strjoin(path_arr[j], "/");
		cmd_path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
		{
			ft_free_tab(path_arr);
			return (cmd_path);
		}
		free(cmd_path);
		j++;
	}
	ft_free_tab(path_arr);
	return (NULL);
}

int	execute_cmd(char **cmds, char **envp)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = get_cmd_path(cmds[0], envp);
	if (!cmd_path || execve(cmd_path, cmds, envp) == -1)
	{
		free(cmd_path);
		return (EXIT_FAILURE);
	}
	free(cmd_path);
	return (EXIT_SUCCESS);
}

void    run_cmd(t_cmd *cmd, char **envp)
{
    //int fd[2];

    t_execcmd   *ecmd;
    t_pipecmd   *pcmd;
    t_redircmd  *rcmd;

    if (!cmd)
        err_msg("cdm doesn't exist");
    if (cmd->type == EXEC)
    {
        ecmd = (t_execcmd *) cmd;
        if (ecmd->argv[0] == 0)
            exit(0);
        execute_cmd(ecmd->argv, envp);
    }
    else if (cmd->type == PIPE)
    {
        pcmd = (t_pipecmd *) cmd;
    }
    else if (cmd->type == REDIR)
    {
        rcmd = (t_redircmd *) cmd;
    }
    exit(0);
}