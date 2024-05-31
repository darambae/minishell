#include "../../minishell.h"

static void	update_env(t_minishell *g_param, char *str, char *new)
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
		g_param->exit_status = 1;
	}
	else
	{
		printf("%s\n", getcwd(NULL, 0));
		update_env(g_param, "OLDPWD=", current_path);
		update_env(g_param, "PWD=", getcwd(NULL, 0));
		printf("OLDPWD=%s\n", get_path("OLDPWD="));
		printf("PWD=%s\n", get_path("PWD="));
		g_param->exit_status = 0;
	}
	//free(path);
	//free(current_path);
}

void	ft_cd(char **argv, t_minishell *g_param)
{
	char	*path;

	path = NULL;
	if (!argv[1] || (!ft_strcmp(argv[1], "~") && !argv[2]))
		path = get_path("HOME=");
	else if (argv[1] && !argv[2])
	{
		if (!ft_strcmp(argv[1], "-"))
			path = get_path("OLDPWD=");
		else
			path = argv[1];
	}
	else if (!ft_strcmp(argv[1], "--") && argv[2][0] == '-')
		path = argv[2];
	else
	{
		perror("cd");
		g_param->exit_status = 1;
	}
	execute_chdir(path, g_param);
	//exit(g_param->exit_status);
}
