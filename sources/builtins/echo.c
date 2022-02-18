/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:04:40 by maroly            #+#    #+#             */
/*   Updated: 2022/02/18 12:51:13 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_b(char **t)
{
	int i;

	i = 1;
	if (t[i] && ft_strcmp(t[i], "-n") == 0)
		while (t[++i] && check_limiter(t[i]) == 0)
			ft_putstr(t[i]);
	else
	{
		while (t[i] && check_limiter(t[i]) == 0)
			ft_putstr(t[i++]);
		write(1, "\n", 1);
	}
}