#include "../../minishell.h"

static void	update_env(char *str, char *new)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_param->env_variables[i])
	{
		if (!ft_strncmp(str, g_param->env_variables[i], ft_strlen(str)))
		{
			tmp = g_param->env_variables[i];
			g_param->env_variables[i] = ft_strjoin(str, new);
			//free(tmp);
			(void)tmp;
			return ;
		}
		i++;
	}
}

static void	execute_chdir(char *path)
{
	char	*current_path;

	current_path = NULL;
	current_path = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("cd");
		g_param->exit_status = 1;
	}
	else
	{
		update_env("OLDPWD=", current_path);
		update_env("PWD=", getcwd(NULL, 0));
		g_param->exit_status = 0;
	}
	//free(path);
	//free(current_path);
}

void	ft_cd(t_execcmd *cmd)
{
	char	*path;

	path = NULL;
	if (!cmd->argv[1] || (!ft_strcmp(cmd->argv[1], "~") && !cmd->argv[2]))
		path = get_path("HOME=");
	else if (cmd->argv[1] && !cmd->argv[2])
	{
		if (!ft_strcmp(cmd->argv[1], "-"))
			path = get_path("OLDPWD=");
		else
			path = cmd->argv[1];
	}
	else if (!ft_strcmp(cmd->argv[1], "--") && cmd->argv[2][0] == '-')
		path = cmd->argv[2];
	else
	{
		perror("cd");
		g_param->exit_status = 1;
	}
	execute_chdir(path);
}
