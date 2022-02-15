/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_base_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:19:15 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 13:19:19 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (ft_strlen(base) < 2 || base[i] == '-'
		|| base[i] == '+' || (base[i] >= 9 && base[i] <= 13) || base[i] == 32)
		return (0);
	while (base[i])
	{
		while (base[j])
		{
			if (base[i] == base[j] || base[j] == '-' || base[j] == '+'
				|| (base[i] >= 9 && base[i] <= 13) || base[i] == 32)
				return (0);
			j++;
		}
		i++;
		j = i + 1;
	}
	return (1);
}
