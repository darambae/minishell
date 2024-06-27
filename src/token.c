/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:55:32 by dabae             #+#    #+#             */
/*   Updated: 2024/06/27 13:55:33 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*skip whitespace and tabs, return true if first carac == c or False if not
or if there is no carac
Set start_str on the next non-whitespace char and check if it's a token.*/
int	peek(char *c, t_minishell *param)
{
	char	*tmp;

	tmp = param->start_line;
	while (tmp < param->end_line && ft_strchr(" \t\n\v\r", *tmp))
		tmp++;
	param->start_line = tmp;
	if (tmp >= param->end_line)
		return (-1);
	return (*tmp && ft_strchr(c, *tmp));
}

static void	assign_token(char **cur, t_minishell *param)
{
	if (**cur == '<')
	{
		if (*(*cur + 1) == '<')
		{
			(*cur)++;
			param->res = '{';
		}
		else
			param->res = '[';
	}
	else if (**cur == '>')
	{
		if (*(*cur + 1) == '>')
		{
			(*cur)++;
			param->res = '}';
		}
		else
			param->res = ']';
	}
}

static void	give_token(char **cur, t_minishell *param)
{
	param->res = **cur;
	if (!**cur)
		param->res = 0;
	else if (**cur == '|')
		param->res = '-';
	else if (**cur == '<' || **cur == '>')
		assign_token(cur, param);
	else
		param->res = 'a';
}

void	handle_token(char **cur, int save, t_minishell *param)
{
	int		i;
	char	quote;

	i = 0;
	quote = 'a';
	if (param->res == 'a')
		i = quote_parsing(cur, i, param, &quote);
	else
		(*cur)++;
	if (quote != 'a')
		ft_error("a quote is not closed", 1);
	if (save)
		param->end_t = *cur - i;
	skip_whitespace(cur, param);
	param->start_line = *cur;
}

/*set start_t on the next non whitespace char, indentify this char and
return a token (redire or word or pipe) and set start_line on the
non whitespace char after start_end*/
int	get_token(int save, t_minishell *param)
{
	char	*cur;

	if (param->start_line >= param->end_line)
		return (0);
	cur = param->start_line;
	skip_whitespace(&cur, param);
	if (save)
		param->start_t = cur;
	give_token(&cur, param);
	handle_token(&cur, save, param);
	return (param->res);
}
