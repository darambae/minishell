#include "../../minishell.h"

static bool check_export_syntax(char **cmd)
{
	int i;

	i = 0;
	if (cmd[1])
	{
		if (ft_isdigit(cmd[1][0]))
			return (false);
		while (cmd[1][i] && (ft_isalpha(cmd[1][i]) || ft_isdigit(cmd[1][i]) || \
			ft_strchr("_" ,cmd[1][i])))
			i++;
		if (!cmd[1][i] || cmd[1][i] == '=')
			return (true);
	}
	return (false);
}

static char **new_arr(char *new, int len_env, int len_name, t_minishell *g_param)
{
	char    **new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(sizeof(char *) * (len_env + 1));
	if (!new_env)
		return NULL;
	i = 0;
	j = 0;
	while (i < len_env)
	{
		if (!g_param->env_variables[i])
		{
			new_env[j] = ft_strdup(new);
			break ;
		}
		if (!ft_strncmp(g_param->env_variables[i], new, len_name))
			new_env[j] = ft_strdup(new);
		else
			new_env[j] = ft_strdup(g_param->env_variables[i]);
		j++;
		i++;
	}
	ft_free_tab(g_param->env_variables);
	return (new_env);
}

void    ft_export(t_execcmd *cmd, t_minishell *g_param)
{
	int     len_name;
	int     j;
	int		len_env;

	len_env = 0;
	while (g_param->env_variables[len_env])
		len_env++;
	len_name = 0;
	if (check_export_syntax(cmd->argv) == false)
	{
		errno = 1;
		perror("export syntax error");
		g_param->exit_status = 1;
		return ;
	}
	while (cmd->argv[1][len_name] != '=' && cmd->argv[1][len_name])
		len_name++;
	j = 0;
	while (g_param->env_variables[j] && ft_strncmp(g_param->env_variables[j], cmd->argv[1], len_name))
		j++;
	if (cmd->argv[1][len_name] == '=')
	{
		if (!g_param->env_variables[j])
			len_env++;
		g_param->env_variables = new_arr(cmd->argv[1], len_env, len_name, g_param);
	}
	exit_status = 0;
}
