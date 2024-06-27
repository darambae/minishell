/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:31:10 by dabae             #+#    #+#             */
/*   Updated: 2024/06/27 11:31:11 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(char **argv, t_minishell *param)
{
	int	i;

	if (argv[1])
	{
		ft_error("env: too many arguments", EINVAL);
		return (1);
	}
	i = 0;
	while (param->env_variables[i])
		printf("%s\n", param->env_variables[i++]);
	return (0);
}
