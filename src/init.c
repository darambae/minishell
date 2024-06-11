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
	t_minishell	*param;

	param = NULL;
	param = (t_minishell *)malloc(sizeof(t_minishell));
	if (param == NULL)
		ft_error("malloc error", 1);
	g_exit_status = 0;
	param->end_line = NULL;
	param->end_t = NULL;
	param->start_line = NULL;
	param->start_t = NULL;
	param->first_cmd = NULL;
	param->env_variables = NULL;
	param->env_variables = make_copy(envp);
	param->exit_status = 0;
	param->cmd_line = NULL;
	param->save_out = dup(STDOUT_FILENO);
	param->save_in = dup(STDIN_FILENO);
	param->arg_to_clean = malloc(sizeof(char *));
	if (!param->arg_to_clean)
		ft_error("a malloc failed in init_param function\n", 1);
	param->arg_to_clean[0] = NULL;
	return (param);
}

void	trim_line(char *line, t_minishell *param)
{
	param->cmd_line = ft_strdup(line);
	param->end_line = param->cmd_line + ft_strlen(param->cmd_line);
	param->start_line = param->cmd_line;
	param->first_cmd = parse(param);
}
