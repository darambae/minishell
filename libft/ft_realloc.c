/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:20:24 by dabae             #+#    #+#             */
/*   Updated: 2024/06/06 07:18:56 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*To reallocate memory but only smaller than the existing size(shrinking)*/
void	*ft_realloc(void *p, size_t new_size)
{
	char	*new_p;
	size_t	cur_size;

	if (!p)
		return (malloc(new_size));
	cur_size = sizeof(p);
	if (new_size <= cur_size)
		return (p);
	new_p = malloc(new_size);
	new_p = NULL;
	ft_memcpy(p, new_p, cur_size);
	free(p);
	return (new_p);
}