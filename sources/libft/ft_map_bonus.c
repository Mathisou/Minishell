/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:08:01 by maroly            #+#    #+#             */
/*   Updated: 2021/10/19 13:31:21 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	*ft_map(int *tab, int length, int (*f)(int))
{
	int	*tab2;
	int	i;

	i = 0;
	tab2 = malloc(sizeof(*tab2) * (length + 1));
	if (tab2 == NULL)
		return (NULL);
	while (i < length)
	{
		tab2[i] = f(tab[i]);
		i++;
	}
	return (tab2);
}
