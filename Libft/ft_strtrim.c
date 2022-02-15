/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:45:09 by maroly            #+#    #+#             */
/*   Updated: 2021/11/28 16:25:58 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	size_to_malloc(const char *str, int j)
{
	int	i;

	i = 0;
	while (str[i] && i < j)
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	j = ft_strlen(s1) - 1;
	i = 0;
	k = 0;
	if (!set || !s1)
		return (NULL);
	while (is_set(s1[i], set) == 1 && s1[i])
		i++;
	while (is_set(s1[j], set) == 1 && j >= 0)
		j--;
	new = malloc(sizeof(*new) * (size_to_malloc(&s1[i], ++j - i) + 1));
	if (new == NULL)
		return (NULL);
	while (s1[i + k] && i + k < j)
	{
		new[k] = s1[i + k];
		k++;
	}
	new[k] = '\0';
	return (new);
}
