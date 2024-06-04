#include "../../minishell.h"

static bool check_unset_syntax(char **cmd)
{
	int i;
	int j;

	i = 1;
	if (!cmd[1])
		return (false);
	else
	{
		while (cmd[i])
		{
			j= 0;
			while (g_param->env_variables[j])
			{
				if (!ft_strncmp(g_param->env_variables[j] ,cmd[i], \
					ft_strlen(cmd[i])))
					return (true);
				j++;
			}
			i++;
		}
		return (false);
	}
}

// static int  count_correspon(char **env, char **argv)
// {
// 	int i;
// 	int j;
// 	int count;

// 	i = 0;
// 	count = 0;
// 	while (argv[i])
// 	{
// 		j = 0;
// 		while (env[j])
// 		{
// 			if (!ft_strncmp(env[j] ,argv[i], ft_strlen(argv[i])))
// 			{
// 				count++;
// 				break;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (count);
//}

// static void remove_elements(char **argv)
// {
// 	char	**new_env;
// 	int		i;

// 	i = 0;
// 	while (argv[i])
// 		i++;
// 	while (g_param->env_variables)
// 	new_env = (char **)malloc(sizeof(char *) * (i + 1));
// 	*new_env = ft_strdup(*argv);
// }

void    ft_unset(t_execcmd *cmd)
{
	int i;
	int j;

	i = 1;
	if (check_unset_syntax(cmd->argv) == false)
	{
		errno = 1;
		perror("unset syntax error");
		g_param->exit_status = 1;
		return ;
	}
	while (cmd->argv[i])
	{
		j = 0;
		while (g_param->env_variables[j])
		{
			if (!ft_strncmp(g_param->env_variables[j] ,cmd->argv[i], \
				ft_strlen(cmd->argv[i])))
			{
				while (g_param->env_variables[j])
				{

					g_param->env_variables[j] = ft_strdup(g_param->env_variables[j + 1]);
					j++;
					if (!g_param->env_variables[j])
						break;
				}
				g_param->env_variables[j] = NULL;
				break ;
			}
			else
				j++;
		}
		i++;
	}
	g_param->exit_status = 0;
}
