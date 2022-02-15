/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:56:38 by maroly            #+#    #+#             */
/*   Updated: 2022/02/03 23:03:47 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*value_to_return(char *new_line, char *buffer, int check)
{
	if (buffer)
		free(buffer);
	if (!new_line || check == -1)
		return (NULL);
	return (new_line);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	else
	{
		while (s[i])
			i++;
	}
	return (i);
}

char	*split(char *str, char *new)
{
	int	i;

	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
