/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:32:16 by dabae             #+#    #+#             */
/*   Updated: 2024/06/28 12:05:21 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* interpret '$?' as exit code */
char	*dollars_exit(char **cur)
{
	char	*s;

	s = NULL;
	(*cur)++;
	s = ft_itoa(g_exit_status);
	return (s);
}

/* fetch the value of the environment variable */
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
	s = get_env_value(ft_strjoin(s, "="), param);
	free(temp);
	temp = NULL;
	return (s);
}

char	*get_env_value(char *s, t_minishell *param)
{
	int		j;
	char	*env;
	int		len;

	j = 0;
	len = ft_strlen(s);
	env = NULL;
	while (param->env_variables[j])
	{
		if (ft_strncmp(s, param->env_variables[j], len) == 0)
		{
			env = ft_strdup(param->env_variables[j] + len);
			break ;
		}
		j++;
	}
	free(s);
	s = NULL;
	return (env);
}

void	dollar_return(t_minishell *param, char *s, char **cur)
{
	char	*temp;

	if (s)
	{
		temp = ft_strjoin(param->start_t, s);
		free(s);
		s = NULL;
	}
	else
		temp = ft_strdup(param->start_t);
	param->start_t = ft_strjoin(temp, *cur);
	*cur = param->start_t + ft_strlen(temp);
	param->end_line = *cur + ft_strlen(*cur);
	save_arg_to_clean(param->start_t, param);
	free(temp);
	temp = NULL;
}

void	dollars_parsing(char **cur, char quote, int *i, t_minishell *param)
{
	char	*s;

	s = NULL;
	if (ft_strchr(" \t\n\v\r", *(*cur + 1)) || *(*cur + 1) == quote)
	{
		*((*cur) - *i) = **cur;
		(*cur)++;
		return ;
	}
	*((*cur) - *i) = '\0';
	*i = 0;
	(*cur)++;
	if (**cur == '?')
		s = dollars_exit(cur);
	else
		s = dollars_env(cur, quote, param);
	dollar_return(param, s, cur);
}
