/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:39:39 by dabae             #+#    #+#             */
/*   Updated: 2024/05/15 15:19:04 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	get_token(char **start_line, char **end_line, char **start_t, char **end_t)
{
	char	*whitespace;
	char	*symbols;
	char	*cur;
	int		token;

	whitespace = " \t\n\v\r";
	symbols = "$\"'|><";
	cur = *start_line;
	while (*cur && ft_strchr(whitespace, *cur))
		cur++;
	if (!*cur)
		return (false);
	*start_t = cur;
	if (ft_strchr(symbols, *cur))
	{
		*end_t = cur + 1;
		*start_line = cur + 1;
		return (true);
	}
	while (*cur && !ft_strchr(whitespace, *cur) && !ft_strchr(symbols, *cur))
		cur++;
	*end_t = cur;
	*start_line = cur;
	return (true);
}