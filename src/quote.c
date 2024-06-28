/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:49:54 by dabae             #+#    #+#             */
/*   Updated: 2024/06/28 12:05:42 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_arg_to_clean(char *s, t_minishell *param)
{
	int		i;
	char	**temp;

	temp = NULL;
	i = 0;
	while (param->arg_to_clean && param->arg_to_clean[i])
		i++;
	i++;
	temp = malloc((i + 1) * sizeof(char *));
	if (!temp)
	{
		ft_error("malloc", 1);
		return ;
	}
	i = 0;
	while (param->arg_to_clean && param->arg_to_clean[i])
	{
		temp[i] = param->arg_to_clean[i];
		i++;
	}
	temp[i++] = s;
	temp[i] = NULL;
	ft_free_tab(param->arg_to_clean);
	param->arg_to_clean = temp;
}

void	skip_whitespace(char **cur, t_minishell *param)
{
	while (*cur < param->end_line && ft_strchr(" \t\n\v\r", **cur))
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
