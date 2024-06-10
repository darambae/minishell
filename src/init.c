#include "../minishell.h"

char	**make_copy(char **env)
{
	char	**copy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (i == 0)
		return (NULL);
	copy = malloc((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_minishell	*init_param(char **envp)
{
	t_minishell	*g_param;

	g_param = (t_minishell *)malloc(sizeof(t_minishell));
	if (g_param == NULL)
	{
		perror("malloc");
		exit(1);
	}
	g_param->end_line = NULL;
	g_param->end_t = NULL;
	g_param->start_line = NULL;
	g_param->start_t = NULL;
	g_param->env_variables = make_copy(envp);
	g_param->exit_status = 0;
	g_param->cmd_line = NULL;
	g_param->save_out = dup(STDOUT_FILENO);
	g_param->save_in = dup(STDIN_FILENO);
	g_param->arg_to_clean = NULL;
	return (g_param);
}

void	trim_line(char *line, t_minishell *g_param)
{
	g_param->cmd_line = ft_strdup(line);
	g_param->end_line = g_param->cmd_line + ft_strlen(g_param->cmd_line);
	g_param->start_line = g_param->cmd_line;
	g_param->first_cmd = parse(g_param);
}
