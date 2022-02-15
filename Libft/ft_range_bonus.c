/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:51:18 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 12:51:24 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	*ft_range(int min, int max)
{
	int	i;
	int	*tab;
	int	size;

	i = 0;
	size = max - min;
	if (min >= max)
		return (0);
	tab = malloc(sizeof(int) * size);
	if (tab == NULL)
		return (NULL);
	while (min < max)
	{
		tab[i] = min;
		i++;
		min++;
	}
	return (tab);
}
