/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:07:23 by maroly            #+#    #+#             */
/*   Updated: 2021/11/21 13:57:28 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	if (((char *)dest) > ((char *)src))
		while (n-- > 0)
			((char *)dest)[n] = ((char *)src)[n];
	else
		while (i++ < n)
			((char *)dest)[i - 1] = ((char *)src)[i - 1];
	return (dest);
}
