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

// void ft_unset(t_execcmd *cmd)
// {
//     int i;
//     int j;
//     int k;

//     i = 1;
//     if (check_unset_syntax(cmd->argv) == false)
//     {
//         errno = 1;
//         perror("unset syntax error");
//         g_param->exit_status = 1;
//         return;
//     }
    
//     while (cmd->argv[i])
//     {
//         j = 0;
//         while (g_param->env_variables[j])
//         {
//             if (!ft_strncmp(g_param->env_variables[j], cmd->argv[i], ft_strlen(cmd->argv[i])) &&
//                 g_param->env_variables[j][ft_strlen(cmd->argv[i])] == '=')
//             {
//                 free(g_param->env_variables[j]);
                
//                 // Shift the remaining environment variables
//                 k = j;
//                 while (g_param->env_variables[k])
//                 {
//                     g_param->env_variables[k] = g_param->env_variables[k + 1];
//                     k++;
//                 }
                
//                 // Null terminate the array after shifting
//                 g_param->env_variables[k] = NULL;
//                 break;
//             }
//             else
//             {
//                 j++;
//             }
//         }
//         i++;
//     }
    
//     g_param->exit_status = 0;
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
                    ft_realloc(g_param->env_variables[j], ft_strlen(g_param->env_variables[j + 1]));
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
