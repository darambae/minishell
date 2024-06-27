/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:32:16 by dabae             #+#    #+#             */
/*   Updated: 2024/06/27 13:54:52 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dollars_exit(char **cur)
{
	char	*s;

	s = NULL;
	(*cur)++;
	s = ft_itoa(g_exit_status);
	return (s);
}

char	*dollars_env(char **cur, char quote, t_minishell *param)
{
	char	*s;
	int		i;
	char	*temp;

	i = 0;
	s = ft_strdup(*cur);
	while (*cur < param->end_line && !ft_strchr(" \t\n\v\r|><", **cur) \
				&& (**cur != quote || quote == 'a'))
	{
		(*cur)++;
		i++;
	}
	s[i] = '\0';
	temp = s;
	s = get_path(ft_strjoin(s, "="), param);
	free(temp);
	return (s);
}

char	*get_path(char *s_redircmd, t_minishell *param)
{
	int		j;
	char	*env;
	int		len;

	j = 0;
	len = ft_strlen(s_redircmd);
	env = NULL;
	while (param->env_variables[j])
	{
		if (ft_strncmp(s_redircmd, param->env_variables[j], len) == 0)
		{
			env = ft_strdup(param->env_variables[j] + len);
			break ;
		}
		j++;
	}
	if (!env)
	{
		free(env);
		return (NULL);
	}
	free(s_redircmd);
	return (env);
}
