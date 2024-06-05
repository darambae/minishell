#include "../../minishell.h"

// static bool element_in_arr(char **argv, char **env)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (argv[i])
// 	{
// 		j = 0;
// 		while (env[j])
// 		{
// 			if (!ft_strncmp(env[j] ,argv[i], ft_strlen(argv[i])))
// 				return (true);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (false);
// }

static int  count_correspon(char **env, char **argv)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		j = 0;
		while (env[j])
		{
			if (!ft_strncmp(env[j] ,argv[i], ft_strlen(argv[i])))
			{
				count++;
				break;
			}
			j++;
		}
		i++;
	}
	return (count);
}

static char **renew_arr(char **argv, int len_arr, t_minishell *g_param)
{
	char	**new_env;
	int		i;
	int		j;
	int		k;
	bool	should_copy;

	new_env = (char **)malloc(sizeof(char *) * (len_arr + 1 - count_correspon(g_param->env_variables, argv)));
	if (!new_env)
		return NULL;
	i = 0;
	k = 0;
	while (g_param->env_variables[i])
	{
        should_copy = true;
        j = 1;
        while (argv[j]) {
            if (!strncmp(g_param->env_variables[i], argv[j], strlen(argv[j])) &&
                (g_param->env_variables[i][strlen(argv[j])] == '=')) {
                should_copy = false;
                break;
            }
            j++;
        }
        if (should_copy)
		{
            new_env[k] = strdup(g_param->env_variables[i]);
            k++;
        }
        i++;
    }
	new_env[k] = NULL;
	ft_free_tab(g_param->env_variables);
	return (new_env);
}

void    ft_unset(t_execcmd *cmd, t_minishell *g_param)
{
	int	len_env;

	len_env = 0;
	while (g_param->env_variables[len_env])
		len_env++;
	if (count_correspon(g_param->env_variables, cmd->argv) > 0)
		g_param->env_variables = renew_arr(cmd->argv, len_env, g_param);
	exit_status = 0;
}
