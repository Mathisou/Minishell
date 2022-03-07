/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:20:29 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 14:46:17 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_line2(char *line, int *i, int *j)
{
	*j = *i;
	while (line[++(*j)] && line[*j] != 34)
		;
	if (line[*j] && line[*j] == 34)
		*i = *j;
	else
		return (1);
	return (0);
}

int	check_line(char *line)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
		{
			if (check_line2(line, &i, &j))
				return (1);
		}
		else if (line[i] == 39)
		{
			j = i;
			while (line[++j] && line[j] != 39)
				continue ;
			if (line[j] && line[j] == 39)
				i = j;
			else
				return (1);
		}
	}
	return (0);
}
