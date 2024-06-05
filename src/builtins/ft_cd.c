#include "../../minishell.h"

static void	update_env(char *str, char *new, t_minishell *g_param)
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

static void	execute_chdir(char *path, t_minishell *g_param)
{
	char	*current_path;

	current_path = NULL;
	current_path = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("cd");
		exit_status = 1;
	}
	else
	{
		update_env("OLDPWD=", current_path, g_param);
		update_env("PWD=", getcwd(NULL, 0), g_param);
		exit_status = 0;
	}
}

void	ft_cd(t_execcmd *cmd, t_minishell *g_param)
{
	char	*path;

	path = NULL;
	if (!cmd->argv[1] || (!ft_strcmp(cmd->argv[1], "~") && !cmd->argv[2]))
		path = get_path("HOME=", g_param);
	else if (cmd->argv[1] && !cmd->argv[2])
	{
		if (!ft_strcmp(cmd->argv[1], "-"))
			path = get_path("OLDPWD=", g_param);
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
	execute_chdir(path, g_param);
}
