/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:36:28 by dabae             #+#    #+#             */
/*   Updated: 2024/06/10 12:41:46 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

int	ft_count_char(char *line, char c)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == c)
			count++;
		line++;
	}
	return (count);
}
