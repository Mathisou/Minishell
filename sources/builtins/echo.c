/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:40 by maroly            #+#    #+#             */
/*   Updated: 2022/02/28 16:59:28 by hkovac           ###   ########.fr       */
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

void	echo_b(char **t)
{
	int	i;
	int	size;

	size = double_tab_len(t);
	i = 1;
	if (t[i] && ft_strcmp(t[i], "-n") == 0)
	{
		while (t[++i] && check_limiter(t[i]) == 0)
		{
			ft_putstr(t[i]);
			if (i < size - 1)
				write(1, " ", 1);
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
