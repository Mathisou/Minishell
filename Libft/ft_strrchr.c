/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:48:46 by maroly            #+#    #+#             */
/*   Updated: 2021/11/23 10:47:25 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;

	size = ft_strlen(s);
	while (size > 0)
	{
		if (s[size] == (unsigned char)c)
			return ((char *)&s[size]);
		size--;
	}
	if (s[size] == (unsigned char)c)
		return ((char *)&s[size]);
	return (NULL);
}
