/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:49:54 by dabae             #+#    #+#             */
/*   Updated: 2024/06/27 15:17:36 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**save_arg_to_clean(char *s, t_minishell *g_param)
{
	int		i;
	char	**temp;

	temp = NULL;
	i = 0;
	while (g_param->arg_to_clean[i])
		i++;
	i++;
	temp = malloc((i + 1) * sizeof(char *));
	if (!temp)
	{
		ft_error("a malloc failed in save_arg_to_clean function", 1);
		return (NULL);
	}
	i = 0;
	while (g_param->arg_to_clean[i])
	{
		temp[i] = g_param->arg_to_clean[i];
		i++;
	}
	temp[i++] = s;
	temp[i] = NULL;
	free(g_param->arg_to_clean);
	g_param->arg_to_clean = NULL;
	return (temp);
}

void	skip_whitespace(char **cur, t_minishell *g_param)
{
	while (*cur < g_param->end_line && ft_strchr(" \t\n\v\r", **cur))
		(*cur)++;
}

int	quote_parsing(char **cur, int i, t_minishell *param, char *quote)
{
	while (**cur && (*quote != 'a' \
		|| (*quote == 'a' && !ft_strchr(" \t\n\v\r|><", **cur))))
	{
		if (*quote != '\'' && **cur == '$')
			dollars_parsing(cur, *quote, &i, param);
		else if (**cur == *quote && *quote != 'a')
		{
			*quote = 'a';
			(*cur)++;
			i++;
		}
		else if (*quote == 'a' && ft_strchr("'\"", **cur))
		{
			*quote = **cur;
			(*cur)++;
			i++;
		}
		else if (**cur)
		{
			*((*cur) - i) = **cur;
			(*cur)++;
		}
	}
	return (i);
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
	param->arg_to_clean = save_arg_to_clean(param->start_t, param);
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
