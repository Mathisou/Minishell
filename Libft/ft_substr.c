/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:24:12 by maroly            #+#    #+#             */
/*   Updated: 2021/11/24 16:53:09 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strncats(char *dest, const char *src, size_t n)
{
	size_t	i;
	int		size;

	i = 0;
	size = ft_strlen(dest);
	while (src[i] && i < n)
	{
		dest[size + i] = (char)src[i];
		i++;
	}
	dest[size + i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
	{
		return (NULL);
	}
	new = NULL;
	while (s[i] && i != start)
		i++;
	while (s[i + j] && j < len)
		j++;
	new = (char *) malloc(sizeof(*new) * (j + 1));
	if (new == NULL)
		return (NULL);
	new[0] = '\0';
	return (ft_strncats(new, &s[i], len));
}
