#include "../../minishell.h"

int	ft_cd(char **argv, t_minishell *g_param)
{
	char	*path;

	path = NULL;
	if (!argv[1] || (!ft_strcmp(argv[1], "~") && !argv[2]))
		path = getenv("HOME");
	else if (argv[1] && !argv[2])
	{
			if (!ft_strcmp(argv[1], "-"))
				path = getenv("OLDPWD");
			else if (argv[1][0] == '/')
			{
				//handle absolute path
			}
			else
			{
				//handle relative path
			}
	}
	else if (argv[1] && argv[2])
	{
		if (!ft_strcmp(argv[1], "--") && argv[2][0] == '-')
		{//go to the file or directory even if the filename starts with '-'
		}
		else 
		{
			printf("cd: invalid option -- '%c'\n", argv[1][1]);
			g_param->exit_status = 1;
		}
	}
		if (chdir(argv[1]) < 0)
		{
			printf("cd: %s: No such file or directory\n", argv[1]);
			g_param->exit_status = 1;
		}
	}
	{
		if (!ft_strcmp(argv[1], "--") && argv[2][0] == '-')
		{//go to the file or directory even if the filename starts with '-'
		}
		else 
		{
			printf("cd: invalid option -- '%c'\n", argv[1][1]);
			g_param->exit_status = 1;
		}
	}
		if (chdir(argv[1]) < 0)
		{
			printf("cd: %s: No such file or directory\n", argv[1]);
			g_param->exit_status = 1;
		}
	}
}