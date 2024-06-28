/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:31:39 by dabae             #+#    #+#             */
/*   Updated: 2024/06/28 15:03:45 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*retrieve all of the available paths on the system*/
static char	**whole_paths(char **envp)
{
	int		j;
	char	*whole_path;
	char	**path_arr;

	j = 0;
	whole_path = NULL;
	path_arr = NULL;
	while (envp[j])
	{
		if (ft_strncmp("PATH=", envp[j], 5) == 0)
		{
			whole_path = ft_strdup(envp[j] + 5);
			path_arr = ft_split(whole_path, ':');
		}
		j++;
	}
	if (!whole_path)
	{
		ft_error("No path found", 127);
		exit(127);
	}
	return (path_arr);
}

/*find the right path for the specific command*/
char	*get_cmd_path(char *cmd_name, char **envp)
{
	int		j;
	char	*cmd_path;
	char	*tmp;
	char	**path_arr;

	path_arr = whole_paths(envp);
	j = -1;
	while (path_arr[++j])
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
	}
	ft_free_tab(path_arr);
	return (NULL);
}

void	execute_cmd(char **cmds, t_minishell *param)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = get_cmd_path(cmds[0], param->env_variables);
	execve(cmd_path, cmds, param->env_variables);
	execve(cmds[0], cmds, param->env_variables);
	free(cmd_path);
	ft_error("command not found", 127);
	exit(127);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork error", 1);
	return (pid);
}

int	heredoc_in_branch(t_cmd *branch)
{
	t_redircmd	*rcmd;

	if (branch->type == EXEC)
		return (1);
	else
	{
		rcmd = (t_redircmd *)branch;
		while (rcmd->token != '{')
		{
			if (rcmd->cmd == NULL || rcmd->cmd->type == EXEC)
				return (1);
			rcmd = (t_redircmd *)rcmd->cmd;
		}
		if (rcmd->token == '{')
			return (0);
	}
	return (1);
}
