/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:13:00 by maroly            #+#    #+#             */
/*   Updated: 2022/03/01 14:46:41 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_delete(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == 34)
		{
			count++;
			while (str[++i] && str[i] != 34)
				;
			count++;
		}
		else if (str[i] == 39)
		{
			count++;
			while (str[++i] && str[i] != 39)
				;
			count++;
		}
	}
	return (count);
}

int	is_there_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == 34 || str[i] == 39)
			return (1);
	return (0);
}

int	is_there_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (1);
	return (0);
}

int	should_replace_var(char *str, int dollarindex)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == dollarindex)
			return (0);
		else if (str[i] == 34)
		{
			while (str[++i] && str[i] != 34)
				;
			if (i > dollarindex)
				return (0);
		}
		else if (str[i] == 39)
		{
			while (str[++i] && str[i] != 39)
				;
			if (i > dollarindex)
				return (1);
		}
	}
	return (0);
}
