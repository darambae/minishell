/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:31:01 by dabae             #+#    #+#             */
/*   Updated: 2024/06/27 11:31:02 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_env(char *str, char *new, t_minishell *param)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = create_double_arr(len_arr(param->env_variables));
	if (!new_env)
		return ;
	i = -1;
	j = 0;
	while (param->env_variables[++i])
	{
		if (!ft_strncmp(param->env_variables[i], new, ft_strlen(new)))
			new_env[j] = ft_strjoin(str, new);
		else
			new_env[j] = ft_strdup(param->env_variables[i]);
		j++;
	}
	ft_free_tab(param->env_variables);
	new_env[j] = NULL;
	param->env_variables = new_env;
}

static void	execute_chdir(char *path, t_minishell *param)
{
	char	*current_path;
	char	*tmp;

	current_path = NULL;
	current_path = getcwd(NULL, 0);
	if (chdir(path) == -1)
		ft_error("cd", ENOENT);
	else
	{
		update_env("OLDPWD=", current_path, param);
		tmp = getcwd(NULL, 0);
		update_env("PWD=", tmp, param);
		free(tmp);
		g_exit_status = 0;
	}
	free(current_path);
}

int	ft_cd(t_execcmd *cmd, t_minishell *param)
{
	char	*path;

	path = NULL;
	if (!cmd->argv[1] || (!ft_strcmp(cmd->argv[1], "~") && !cmd->argv[2]))
		path = get_path("HOME=", param);
	else if (cmd->argv[1] && !cmd->argv[2])
	{
		if (!ft_strcmp(cmd->argv[1], "-"))
			path = get_path("OLDPWD=", param);
		else if (cmd->argv[1][0] == '-' && ft_strlen(cmd->argv[1]) > 1)
			return (ft_error("cd: invalid option", 2));
		else
			path = ft_strdup(cmd->argv[1]);
	}
	else if (!ft_strcmp(cmd->argv[1], "--") && cmd->argv[2][0] == '-')
		path = ft_strdup(cmd->argv[2]);
	else
		return (ft_error("cd: too many arguments", 1));
	execute_chdir(path, param);
	free(path);
	return (0);
}
