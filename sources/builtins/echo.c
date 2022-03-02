/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:40 by maroly            #+#    #+#             */
/*   Updated: 2022/03/02 01:50:55 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_tab_len(char **t)
{
	int	i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}

int	strcmp_opt(char *s)
{
	int i;

	i = 0;
	if (s)
	{
		if (s[i] == '-')
		{
			while (s[++i] == 'n')
				;
			if (s[i] == '\0')
				return (0);
			else
				return (1);
		}
	}
	return (1);
}

void	echo_b(char **t)
{
	int	i;
	int	size;

	size = double_tab_len(t);
	i = 1;
	if (t[i] && strcmp_opt(t[i]) == 0)
	{
		while (strcmp_opt(t[++i]) == 0)
			;
		while (t[i] && check_limiter(t[i]) == 0)
		{
			ft_putstr(t[i]);
			if (i < size - 1)
				write(1, " ", 1);
			i++;
		}
	}
	else
	{
		while (t[i] && check_limiter(t[i]) == 0)
		{
			ft_putstr(t[i]);
			if (i < size - 1)
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
	}
}
