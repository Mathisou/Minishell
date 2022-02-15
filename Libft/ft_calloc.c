/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:21:33 by maroly            #+#    #+#             */
/*   Updated: 2021/11/25 18:26:13 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tab;

	tab = NULL;
	tab = (unsigned char *) malloc(sizeof(*tab) * (nmemb * size));
	if (tab == NULL)
		return (NULL);
	ft_memset(tab, 0, nmemb * size);
	return (tab);
}
