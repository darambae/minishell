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

static char **new_arr(char **prev, char *new)
{
    char    **new_env;
    int	len_env;

	len_env = 0;
	while (g_param->env_variables[len_env])
		len_env++;
    new_env = (char **)malloc(sizeof(char *) * (len_env + 1));
	if (!new_env)
		return NULL;
}

void    ft_export(t_execcmd *cmd)
{
    int     i;
    int     j;

    i = 0;
    if (check_export_syntax(cmd->argv) == false)
    {
        errno = 1;
        perror("export syntax error");
        g_param->exit_status = 1;
        return ;
    }
    while (cmd->argv[1][i] != '=' && cmd->argv[1][i])
        i++;
    j = 0;
    while (g_param->env_variables[j] && ft_strncmp(g_param->env_variables[j], cmd->argv[1], i))
        j++;
    if (cmd->argv[1][i] == '=')
    {
        ft_realloc(g_param->env_variables[j], ft_strlen(cmd->argv[1]));
        g_param->env_variables[j] = ft_strdup(cmd->argv[1]);
    }
        //tmp = g_param->env_variables[j];
        //free(tmp);
        
}
