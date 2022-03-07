/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truc_de_merde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:20:54 by maroly            #+#    #+#             */
/*   Updated: 2022/03/07 15:26:02 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tdm(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	check_chev2(char *str, int *i)
{
	int	count;

	count = 0;
	if (str[*i] == 60)
	{
		while (str[*i] && str[(*i)++] == 60)
			count++;
		if (count > 2)
			return (1);
		if (str[*i] && str[*i] == 62)
			return (2);
	}
	else if (str[*i] == 62)
	{
		while (str[*i] && str[(*i)++] == 62)
			count++;
		if (count > 2)
			return (1);
		if (str[*i] && str[*i] == 60)
			return (2);
	}
	return (0);
}

int	check_chev(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34)
			while (str[++i] && str[i] != 34)
				;
		else if (str[i] == 39)
			while (str[++i] && str[i] != 39)
				;
		else
			if (check_chev2(str, &i))
				return (1);
	}
	return (0);
}
