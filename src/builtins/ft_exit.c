/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:31:12 by dabae             #+#    #+#             */
/*   Updated: 2024/06/28 09:00:46 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	set_minus(const char *nptr, int *i, int *sign)
{
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

static int	grep_only_num(const char *nptr)
{
	int	sign;
	int	res;
	int	i;

	sign = 1;
	res = 0;
	i = 0;
	set_minus(nptr, &i, &sign);
	if (nptr[i] == '"')
	{
		i++;
		set_minus(nptr, &i, &sign);
		while (ft_isdigit(nptr[i]))
			res = res * 10 + (nptr[i++] - '0');
		if (nptr[i] == '"')
			return (res * sign);
		else
			return (ft_error("exit syntax error", 2));
	}
	while (ft_isdigit(nptr[i]))
		res = res * 10 + (nptr[i++] - '0');
	return (res * sign);
}

static bool	check_quote(char *num, int i)
{
	if (num[i] == '"')
	{
		i++;
		if (num[i] == '-' || num[i] == '+')
			i++;
		while (num[i] && ft_isdigit(num[i]))
			i++;
		if (num[i] == '"')
			return (true);
		else
			return (false);
	}
	else
		return (true);
}

static int	syntax_check(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	if (check_quote(num, i) == false)
		return (false);
	else
		i++;
	while (num[i])
	{
		if (num[i] == '"')
			break ;
		if (num[i] == '-' || num[i] == '+')
			i++;
		else if (!ft_isdigit(num[i]))
			return (false);
		else
			i++;
	}
	return (true);
}

void	ft_exit(char **cmds)
{
	if (!cmds[1])
	{
		g_exit_status = 0;
		return ;
	}
	if (!syntax_check(cmds[1]))
	{
		ft_error("numeric argument required", 2);
		return ;
	}
	if (cmds[1] && cmds[2])
		ft_error("exit: too many arguments", 1);
	else if (cmds[1] && syntax_check(cmds[1]))
		g_exit_status = grep_only_num(cmds[1]) % 256;
}
